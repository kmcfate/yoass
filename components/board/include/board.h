#pragma once

#include "esp_err.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_touch.h"
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ── Display geometry (shared by both boards) ───────────────────────────── */
#define BOARD_LCD_H_RES     368
#define BOARD_LCD_V_RES     448
#define BOARD_LCD_BIT_PER_PIXEL 16

/* ── I2C bus device addresses ───────────────────────────────────────────── */
#define BOARD_I2C_ADDR_TOUCH    0x38  /* FT3168 / FT6146 */
#define BOARD_I2C_ADDR_IMU      0x6A  /* QMI8658 (SDO low); 0x6B if SDO high */
#define BOARD_I2C_ADDR_PMIC     0x34  /* AXP2101 */
#define BOARD_I2C_ADDR_RTC      0x51  /* PCF85063 */

/* ── Pin definitions ────────────────────────────────────────────────────── */

#if CONFIG_YOASS_BOARD_ESP32_C6_AMOLED_1_8

/* I2C — verify against https://www.waveshare.com/wiki/ESP32-C6-Touch-AMOLED-1.8
 * and https://github.com/waveshareteam/ESP32-C6-Touch-AMOLED-1.8            */
#warning "C6 I2C pins unverified — check schematic before use"
#define BOARD_I2C_SDA       6
#define BOARD_I2C_SCL       7

/* SH8601 QSPI interface — verify against schematic */
#warning "C6 QSPI pins unverified — check schematic before use"
#define BOARD_LCD_QSPI_CLK  1
#define BOARD_LCD_QSPI_CS   2
#define BOARD_LCD_QSPI_D0   3
#define BOARD_LCD_QSPI_D1   4
#define BOARD_LCD_QSPI_D2   5
#define BOARD_LCD_QSPI_D3   10
#define BOARD_LCD_RST       -1   /* Reset via PMIC; -1 = not a direct GPIO */

/* Touch interrupt (active-low, optional) */
#define BOARD_TOUCH_INT     -1   /* Set if wired to a GPIO */

#elif CONFIG_YOASS_BOARD_ESP32_S3_AMOLED_1_8

/* I2C — verify against https://www.waveshare.com/wiki/ESP32-S3-Touch-AMOLED-1.8
 * and https://github.com/waveshareteam/ESP32-S3-Touch-AMOLED-1.8            */
#warning "S3 I2C pins unverified — check schematic before use"
#define BOARD_I2C_SDA       6
#define BOARD_I2C_SCL       7

/* SH8601 QSPI interface — verify against schematic */
#warning "S3 QSPI pins unverified — check schematic before use"
#define BOARD_LCD_QSPI_CLK  47
#define BOARD_LCD_QSPI_CS   9
#define BOARD_LCD_QSPI_D0   18
#define BOARD_LCD_QSPI_D1   17
#define BOARD_LCD_QSPI_D2   16
#define BOARD_LCD_QSPI_D3   15
#define BOARD_LCD_RST       -1

#define BOARD_TOUCH_INT     -1

/* microSD (S3 only) — verify against schematic */
#define BOARD_SD_CLK        12
#define BOARD_SD_CMD        11
#define BOARD_SD_D0         13

#else
#error "No YOASS_BOARD target selected. Run: idf.py menuconfig"
#endif

/* ── Public API ─────────────────────────────────────────────────────────── */

/**
 * @brief Initialize all board peripherals.
 *
 * Initialises (in order): I2C bus, AXP2101 PMIC, SH8601 display,
 * FT3168 touch controller, QMI8658 IMU, PCF85063 RTC, and LVGL port.
 *
 * @return ESP_OK on success, or an error code from the failing peripheral.
 */
esp_err_t board_init(void);

/**
 * @brief Return the initialized LCD panel handle (valid after board_init).
 */
esp_lcd_panel_handle_t board_get_lcd_panel(void);

/**
 * @brief Return the initialized touch handle (valid after board_init).
 */
esp_lcd_touch_handle_t board_get_touch(void);

#ifdef __cplusplus
}
#endif
