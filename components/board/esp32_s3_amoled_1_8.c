#include "sdkconfig.h"

#if CONFIG_YOASS_BOARD_ESP32_S3_AMOLED_1_8

#include "board.h"
#include "driver/i2c_master.h"
#include "driver/spi_master.h"
#include "esp_io_expander_tca9554.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_sh8601.h"
#include "esp_lcd_touch_ft5x06.h"
#include "esp_lvgl_port.h"
#include "esp_log.h"
#include "esp_check.h"

static const char *TAG = "board_s3";

static i2c_master_bus_handle_t  s_i2c_bus   = NULL;
static esp_io_expander_handle_t s_expander  = NULL;
static esp_lcd_panel_handle_t   s_panel     = NULL;
static esp_lcd_touch_handle_t   s_touch     = NULL;

/* ── I2C ──────────────────────────────────────────────────────────────── */

static esp_err_t init_i2c(void)
{
    const i2c_master_bus_config_t cfg = {
        .i2c_port          = BOARD_I2C_NUM,
        .sda_io_num        = BOARD_I2C_SDA,
        .scl_io_num        = BOARD_I2C_SCL,
        .clk_source        = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    ESP_RETURN_ON_ERROR(
        i2c_new_master_bus(&cfg, &s_i2c_bus),
        TAG, "I2C bus init");
    ESP_LOGI(TAG, "I2C ready (SDA=%d SCL=%d)", BOARD_I2C_SDA, BOARD_I2C_SCL);
    return ESP_OK;
}

/* ── IO Expander (TCA9554) ────────────────────────────────────────────── */

static esp_err_t init_io_expander(void)
{
    ESP_RETURN_ON_ERROR(
        esp_io_expander_new_i2c_tca9554(
            s_i2c_bus,
            BOARD_I2C_ADDR_EXPANDER,
            &s_expander),
        TAG, "TCA9554 init");
    ESP_LOGI(TAG, "IO expander (TCA9554@0x%02X) ready", BOARD_I2C_ADDR_EXPANDER);
    return ESP_OK;
}

/* ── Display (SH8601 via QSPI) ────────────────────────────────────────── */

static esp_err_t init_display(void)
{
    esp_lcd_panel_io_handle_t io_handle = NULL;

    const spi_bus_config_t bus_cfg = {
        .sclk_io_num     = BOARD_LCD_QSPI_CLK,
        .data0_io_num    = BOARD_LCD_QSPI_D0,
        .data1_io_num    = BOARD_LCD_QSPI_D1,
        .data2_io_num    = BOARD_LCD_QSPI_D2,
        .data3_io_num    = BOARD_LCD_QSPI_D3,
        .max_transfer_sz = BOARD_LCD_H_RES * BOARD_LCD_V_RES * sizeof(uint16_t),
    };
    ESP_RETURN_ON_ERROR(
        spi_bus_initialize(BOARD_LCD_HOST, &bus_cfg, SPI_DMA_CH_AUTO),
        TAG, "SPI bus init");

    const esp_lcd_panel_io_spi_config_t io_cfg = {
        .cs_gpio_num      = BOARD_LCD_QSPI_CS,
        .dc_gpio_num      = -1,
        .spi_mode         = 0,
        .pclk_hz          = BOARD_LCD_QSPI_FREQ_HZ,
        .trans_queue_depth = 10,
        .lcd_cmd_bits     = 32,
        .lcd_param_bits   = 8,
    };
    ESP_RETURN_ON_ERROR(
        esp_lcd_new_panel_io_spi(
            (esp_lcd_spi_bus_handle_t)BOARD_LCD_HOST, &io_cfg, &io_handle),
        TAG, "LCD IO init");

    const esp_lcd_panel_dev_config_t panel_cfg = {
        .reset_gpio_num = BOARD_LCD_RST,
        .color_space    = ESP_LCD_COLOR_SPACE_RGB,
        .bits_per_pixel = BOARD_LCD_BITS_PER_PX,
    };
    ESP_RETURN_ON_ERROR(
        esp_lcd_new_panel_sh8601(io_handle, &panel_cfg, &s_panel),
        TAG, "SH8601 panel init");

    ESP_RETURN_ON_ERROR(esp_lcd_panel_reset(s_panel),             TAG, "panel reset");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_init(s_panel),              TAG, "panel init");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_disp_on_off(s_panel, true), TAG, "display on");

    ESP_LOGI(TAG, "SH8601 display ready (%dx%d)", BOARD_LCD_H_RES, BOARD_LCD_V_RES);
    return ESP_OK;
}

/* ── Touch (FT3168 via I2C) ───────────────────────────────────────────── */

static esp_err_t init_touch(void)
{
    esp_lcd_panel_io_handle_t tp_io = NULL;

    const esp_lcd_panel_io_i2c_config_t tp_io_cfg = {
        .dev_addr            = BOARD_I2C_ADDR_TOUCH,
        .scl_speed_hz        = BOARD_I2C_FREQ_HZ,
        .control_phase_bytes = 1,
        .lcd_cmd_bits        = 8,
        .lcd_param_bits      = 8,
        .flags.disable_control_phase = true,
    };
    ESP_RETURN_ON_ERROR(
        esp_lcd_new_panel_io_i2c(s_i2c_bus, &tp_io_cfg, &tp_io),
        TAG, "touch IO init");

    const esp_lcd_touch_config_t tp_cfg = {
        .x_max        = BOARD_LCD_H_RES,
        .y_max        = BOARD_LCD_V_RES,
        .rst_gpio_num = BOARD_TOUCH_RST,
        .int_gpio_num = BOARD_TOUCH_INT,
        .flags        = { .swap_xy = 0, .mirror_x = 0, .mirror_y = 0 },
    };
    ESP_RETURN_ON_ERROR(
        esp_lcd_touch_new_i2c_ft5x06(tp_io, &tp_cfg, &s_touch),
        TAG, "FT5x06 touch init");

    ESP_LOGI(TAG, "FT3168 touch ready (INT=%d)", BOARD_TOUCH_INT);
    return ESP_OK;
}

/* ── LVGL port ────────────────────────────────────────────────────────── */

static esp_err_t init_lvgl(void)
{
    const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    ESP_RETURN_ON_ERROR(lvgl_port_init(&lvgl_cfg), TAG, "LVGL port init");

    const lvgl_port_display_cfg_t disp_cfg = {
        .io_handle     = NULL,
        .panel_handle  = s_panel,
        .buffer_size   = BOARD_LCD_H_RES * CONFIG_BOARD_LCD_DRAW_BUF_LINES,
        .double_buffer = true,
        .hres          = BOARD_LCD_H_RES,
        .vres          = BOARD_LCD_V_RES,
        .monochrome    = false,
        .rotation      = { .swap_xy = false, .mirror_x = false, .mirror_y = false },
        /* S3R8 has 8 MB octal PSRAM — use it for LVGL draw buffers */
        .flags         = { .buff_dma = false, .buff_spiram = true },
    };
    lv_display_t *disp = lvgl_port_add_disp(&disp_cfg);
    if (!disp) {
        ESP_LOGE(TAG, "lvgl_port_add_disp failed");
        return ESP_FAIL;
    }

    const lvgl_port_touch_cfg_t touch_cfg = { .disp = disp, .handle = s_touch };
    if (!lvgl_port_add_touch(&touch_cfg)) {
        ESP_LOGE(TAG, "lvgl_port_add_touch failed");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "LVGL port ready (PSRAM buffers)");
    return ESP_OK;
}

/* ── Public API ───────────────────────────────────────────────────────── */

esp_err_t board_init(void)
{
    ESP_LOGI(TAG, "%s", BOARD_NAME);
    ESP_RETURN_ON_ERROR(init_i2c(),         TAG, "I2C");
    ESP_RETURN_ON_ERROR(init_io_expander(), TAG, "IO expander");
    ESP_RETURN_ON_ERROR(init_display(),     TAG, "display");
    ESP_RETURN_ON_ERROR(init_touch(),       TAG, "touch");
    ESP_RETURN_ON_ERROR(init_lvgl(),        TAG, "LVGL");
    return ESP_OK;
}

esp_lcd_panel_handle_t board_get_lcd_panel(void) { return s_panel; }
esp_lcd_touch_handle_t board_get_touch(void)     { return s_touch; }

#endif /* CONFIG_YOASS_BOARD_ESP32_S3_AMOLED_1_8 */
