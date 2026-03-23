#include "sdkconfig.h"

#if CONFIG_YOASS_BOARD_ESP32_C6_AMOLED_1_8

#include "board.h"
#include "driver/i2c_master.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_sh8601.h"
#include "esp_lcd_touch_ft5x06.h"
#include "esp_lvgl_port.h"
#include "esp_log.h"

static const char *TAG = "board_c6";

/* Module-level handles */
static esp_lcd_panel_handle_t  s_panel    = NULL;
static esp_lcd_touch_handle_t  s_touch    = NULL;
static i2c_master_bus_handle_t s_i2c_bus  = NULL;

/* ── I2C ──────────────────────────────────────────────────────────────── */

static esp_err_t init_i2c(void)
{
    i2c_master_bus_config_t cfg = {
        .i2c_port      = I2C_NUM_0,
        .sda_io_num    = BOARD_I2C_SDA,
        .scl_io_num    = BOARD_I2C_SCL,
        .clk_source    = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    return i2c_new_master_bus(&cfg, &s_i2c_bus);
}

/* ── Display (SH8601 via QSPI) ────────────────────────────────────────── */

static esp_err_t init_display(void)
{
    esp_lcd_panel_io_handle_t io_handle = NULL;

    /* QSPI bus */
    esp_lcd_panel_io_spi_config_t io_cfg = {
        .cs_gpio_num        = BOARD_LCD_QSPI_CS,
        .dc_gpio_num        = -1,          /* SH8601 uses SPI mode without DC */
        .spi_clock_hz       = 40 * 1000 * 1000,
        .lcd_cmd_bits       = 32,
        .lcd_param_bits     = 8,
        .flags.quad_mode    = 1,
    };

    /* SPI bus */
    spi_bus_config_t bus_cfg = {
        .sclk_io_num  = BOARD_LCD_QSPI_CLK,
        .data0_io_num = BOARD_LCD_QSPI_D0,
        .data1_io_num = BOARD_LCD_QSPI_D1,
        .data2_io_num = BOARD_LCD_QSPI_D2,
        .data3_io_num = BOARD_LCD_QSPI_D3,
        .max_transfer_sz = BOARD_LCD_H_RES * BOARD_LCD_V_RES * (BOARD_LCD_BIT_PER_PIXEL / 8),
    };
    ESP_RETURN_ON_ERROR(
        spi_bus_initialize(SPI2_HOST, &bus_cfg, SPI_DMA_CH_AUTO),
        TAG, "SPI bus init failed");

    ESP_RETURN_ON_ERROR(
        esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI2_HOST, &io_cfg, &io_handle),
        TAG, "LCD IO init failed");

    esp_lcd_panel_dev_config_t panel_cfg = {
        .reset_gpio_num = BOARD_LCD_RST,
        .rgb_ele_order  = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = BOARD_LCD_BIT_PER_PIXEL,
    };
    ESP_RETURN_ON_ERROR(
        esp_lcd_new_panel_sh8601(io_handle, &panel_cfg, &s_panel),
        TAG, "SH8601 panel init failed");

    ESP_RETURN_ON_ERROR(esp_lcd_panel_reset(s_panel),   TAG, "panel reset");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_init(s_panel),    TAG, "panel init");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_disp_on_off(s_panel, true), TAG, "display on");

    ESP_LOGI(TAG, "SH8601 display initialised (%dx%d)", BOARD_LCD_H_RES, BOARD_LCD_V_RES);
    return ESP_OK;
}

/* ── Touch (FT3168 / FT6146 via I2C) ─────────────────────────────────── */

static esp_err_t init_touch(void)
{
    esp_lcd_panel_io_handle_t tp_io = NULL;

    esp_lcd_panel_io_i2c_config_t tp_io_cfg = {
        .dev_addr          = BOARD_I2C_ADDR_TOUCH,
        .control_phase_bytes = 1,
        .lcd_cmd_bits      = 8,
        .lcd_param_bits    = 8,
        .flags.disable_control_phase = 1,
    };
    ESP_RETURN_ON_ERROR(
        esp_lcd_new_panel_io_i2c(s_i2c_bus, &tp_io_cfg, &tp_io),
        TAG, "touch IO init");

    esp_lcd_touch_config_t tp_cfg = {
        .x_max        = BOARD_LCD_H_RES,
        .y_max        = BOARD_LCD_V_RES,
        .rst_gpio_num = -1,
        .int_gpio_num = BOARD_TOUCH_INT,
        .flags        = { .swap_xy = 0, .mirror_x = 0, .mirror_y = 0 },
    };
    ESP_RETURN_ON_ERROR(
        esp_lcd_touch_new_i2c_ft5x06(tp_io, &tp_cfg, &s_touch),
        TAG, "FT5x06 touch init");

    ESP_LOGI(TAG, "FT3168 touch initialised");
    return ESP_OK;
}

/* ── LVGL port ────────────────────────────────────────────────────────── */

static esp_err_t init_lvgl(void)
{
    const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    ESP_RETURN_ON_ERROR(lvgl_port_init(&lvgl_cfg), TAG, "LVGL port init");

    const lvgl_port_display_cfg_t disp_cfg = {
        .io_handle    = NULL,   /* set by lvgl_port_add_disp internally */
        .panel_handle = s_panel,
        .buffer_size  = BOARD_LCD_H_RES * 40,
        .double_buffer = true,
        .hres  = BOARD_LCD_H_RES,
        .vres  = BOARD_LCD_V_RES,
        .monochrome    = false,
        .rotation.swap_xy  = false,
        .rotation.mirror_x = false,
        .rotation.mirror_y = false,
        .flags.buff_dma    = true,
    };
    lv_display_t *disp = lvgl_port_add_disp(&disp_cfg);
    if (!disp) {
        ESP_LOGE(TAG, "lvgl_port_add_disp failed");
        return ESP_FAIL;
    }

    const lvgl_port_touch_cfg_t touch_cfg = {
        .disp   = disp,
        .handle = s_touch,
    };
    if (!lvgl_port_add_touch(&touch_cfg)) {
        ESP_LOGE(TAG, "lvgl_port_add_touch failed");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "LVGL port initialised");
    return ESP_OK;
}

/* ── Public API ───────────────────────────────────────────────────────── */

esp_err_t board_init(void)
{
    ESP_LOGI(TAG, "Waveshare ESP32-C6-Touch-AMOLED-1.8");
    ESP_RETURN_ON_ERROR(init_i2c(),     TAG, "I2C init");
    ESP_RETURN_ON_ERROR(init_display(), TAG, "display init");
    ESP_RETURN_ON_ERROR(init_touch(),   TAG, "touch init");
    ESP_RETURN_ON_ERROR(init_lvgl(),    TAG, "LVGL init");
    return ESP_OK;
}

esp_lcd_panel_handle_t board_get_lcd_panel(void) { return s_panel; }
esp_lcd_touch_handle_t board_get_touch(void)     { return s_touch; }

#endif /* CONFIG_YOASS_BOARD_ESP32_C6_AMOLED_1_8 */
