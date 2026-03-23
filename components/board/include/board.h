#pragma once

#include "esp_err.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_touch.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ── Display geometry (shared by both boards) ───────────────────────────── */
#define BOARD_LCD_H_RES          368
#define BOARD_LCD_V_RES          448
#define BOARD_LCD_BITS_PER_PX    16            /* RGB565 */
#define BOARD_LCD_QSPI_FREQ_HZ   (40 * 1000 * 1000)

/* ── I2C device addresses ───────────────────────────────────────────────── */
#define BOARD_I2C_ADDR_TOUCH     0x38   /* FT3168 / FT6146 */
#define BOARD_I2C_ADDR_IMU       0x6B   /* QMI8658 (SDO=VCC); use 0x6A if SDO=GND */
#define BOARD_I2C_ADDR_PMIC      0x34   /* AXP2101 */
#define BOARD_I2C_ADDR_RTC       0x51   /* PCF85063 */
#define BOARD_I2C_ADDR_EXPANDER  0x20   /* TCA9554 IO expander (A0/A1/A2=GND) */

/* ── Pin definitions ────────────────────────────────────────────────────── */

#if CONFIG_YOASS_BOARD_ESP32_C6_AMOLED_1_8

/* Source: waveshareteam/ESP32-C6-Touch-AMOLED-1.8
 *   examples/ESP-IDF-v5.5.1/05_LVGL_WITH_RAM/main/example_qspi_with_ram.c
 *   examples/ESP-IDF-v5.5.1/01_AXP2101/sdkconfig.defaults               */
#define BOARD_NAME               "Waveshare ESP32-C6-Touch-AMOLED-1.8"

/* SH8601 QSPI (SPI2_HOST) */
#define BOARD_LCD_HOST           SPI2_HOST
#define BOARD_LCD_QSPI_CLK       GPIO_NUM_0
#define BOARD_LCD_QSPI_CS        GPIO_NUM_5
#define BOARD_LCD_QSPI_D0        GPIO_NUM_1
#define BOARD_LCD_QSPI_D1        GPIO_NUM_2
#define BOARD_LCD_QSPI_D2        GPIO_NUM_3
#define BOARD_LCD_QSPI_D3        GPIO_NUM_4
#define BOARD_LCD_RST            GPIO_NUM_NC   /* Driven by TCA9554 IO expander */

/* I2C (shared by touch, IMU, RTC, PMIC, IO expander) */
#define BOARD_I2C_NUM            I2C_NUM_0
#define BOARD_I2C_SDA            GPIO_NUM_8
#define BOARD_I2C_SCL            GPIO_NUM_7
#define BOARD_I2C_FREQ_HZ        200000

/* Touch */
#define BOARD_TOUCH_RST          GPIO_NUM_NC
#define BOARD_TOUCH_INT          GPIO_NUM_15

/* Audio codec — verify against schematic before use; pins may conflict
 * with QSPI when both are used simultaneously.               */
#define BOARD_I2S_SCLK           GPIO_NUM_3    /* NOTE: same net as QSPI_D2 — VERIFY */
#define BOARD_I2S_MCLK           GPIO_NUM_15   /* VERIFY */
#define BOARD_I2S_WS             GPIO_NUM_5    /* VERIFY */
#define BOARD_I2S_DOUT           GPIO_NUM_6    /* VERIFY */
#define BOARD_I2S_DSIN           GPIO_NUM_4    /* NOTE: same net as QSPI_D3 — VERIFY */
#define BOARD_I2S_AMP_EN         GPIO_NUM_NC   /* VERIFY */

#elif CONFIG_YOASS_BOARD_ESP32_S3_AMOLED_1_8

/* Source: waveshareteam/Waveshare-ESP32-components
 *   bsp/esp32_s3_touch_amoled_1_8/include/bsp/esp32_s3_touch_amoled_1_8.h */
#define BOARD_NAME               "Waveshare ESP32-S3-Touch-AMOLED-1.8"

/* SH8601 QSPI (SPI2_HOST) */
#define BOARD_LCD_HOST           SPI2_HOST
#define BOARD_LCD_QSPI_CLK       GPIO_NUM_11
#define BOARD_LCD_QSPI_CS        GPIO_NUM_12
#define BOARD_LCD_QSPI_D0        GPIO_NUM_4
#define BOARD_LCD_QSPI_D1        GPIO_NUM_5
#define BOARD_LCD_QSPI_D2        GPIO_NUM_6
#define BOARD_LCD_QSPI_D3        GPIO_NUM_7
#define BOARD_LCD_RST            GPIO_NUM_NC   /* Driven by TCA9554 IO expander */

/* I2C (shared by touch, IMU, RTC, PMIC, IO expander) */
#define BOARD_I2C_NUM            I2C_NUM_0
#define BOARD_I2C_SDA            GPIO_NUM_15
#define BOARD_I2C_SCL            GPIO_NUM_14
#define BOARD_I2C_FREQ_HZ        200000

/* Touch */
#define BOARD_TOUCH_RST          GPIO_NUM_NC
#define BOARD_TOUCH_INT          GPIO_NUM_21

/* Audio codec */
#define BOARD_I2S_SCLK           GPIO_NUM_9
#define BOARD_I2S_MCLK           GPIO_NUM_16
#define BOARD_I2S_WS             GPIO_NUM_45
#define BOARD_I2S_DOUT           GPIO_NUM_8
#define BOARD_I2S_DSIN           GPIO_NUM_10
#define BOARD_I2S_AMP_EN         GPIO_NUM_46

/* microSD (SDMMC 1-bit) */
#define BOARD_SD_CLK             GPIO_NUM_2
#define BOARD_SD_CMD             GPIO_NUM_1
#define BOARD_SD_D0              GPIO_NUM_3

#else
#error "No YOASS_BOARD selected. Run: idf.py set-target <esp32c6|esp32s3> && idf.py menuconfig"
#endif

/* ── Public API ─────────────────────────────────────────────────────────── */

/**
 * @brief Initialize all board peripherals.
 *
 * Sequence: I2C bus → TCA9554 IO expander → AXP2101 PMIC →
 *           SH8601 display → FT3168 touch → QMI8658 IMU →
 *           PCF85063 RTC → LVGL port.
 *
 * @return ESP_OK on success, propagated error code on failure.
 */
esp_err_t board_init(void);

/** @brief Return the LCD panel handle (valid after board_init). */
esp_lcd_panel_handle_t board_get_lcd_panel(void);

/** @brief Return the touch handle (valid after board_init). */
esp_lcd_touch_handle_t board_get_touch(void);

#ifdef __cplusplus
}
#endif
