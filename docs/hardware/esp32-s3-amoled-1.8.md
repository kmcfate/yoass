# Waveshare ESP32-S3-Touch-AMOLED-1.8

## Overview

Compact 1.8-inch AMOLED development board based on the ESP32-S3R8 SoC.
Adds 8 MB stacked octal PSRAM and a microSD card slot compared to the C6 variant,
while sharing the same display, touch, IMU, RTC, PMIC, and IO expander ICs.

## Specifications

| Feature | Detail |
|---------|--------|
| **SoC** | ESP32-S3R8, Xtensa LX7 32-bit dual-core |
| **CPU speed** | Up to 240 MHz |
| **Flash** | 16 MB (external, QIO) |
| **RAM** | 512 KB SRAM + 384 KB ROM (internal) |
| **PSRAM** | 8 MB octal (stacked, R8 variant) |
| **Wi-Fi** | 802.11 b/g/n (Wi-Fi 4), 2.4 GHz, onboard antenna |
| **Bluetooth** | BLE 5 |
| **Display** | 1.8" AMOLED, 368 × 448 px, 16.7 M colors |
| **Display driver** | SH8601, QSPI interface |
| **Touch** | FT3168, I2C interface (10 kHz – 400 kHz) |
| **IO expander** | TCA9554, I2C (controls LCD reset and power rails) |
| **IMU** | QMI8658, 6-axis (16-bit accel + gyro) |
| **RTC** | PCF85063, backup battery pads onboard |
| **PMIC** | AXP2101 (LiPo charge/discharge + rail management) |
| **Audio** | Audio codec, built-in microphone, speaker header; offline speech recognition |
| **Storage** | TF (microSD) card slot |
| **Expansion** | 15-pin 1 mm pitch header: 7 × GPIO, 1 × I2C, 1 × UART, 1 × USB, VBUS, 3.3 V, GND |
| **USB** | Type-C (native ESP32-S3 USB, flashing + debugging) |
| **Battery** | 3.7 V LiPo via MX1.25 header (recommended 400 mAh, 3.85 × 24 × 28 mm) |

### Battery Life (400 mAh)

| Mode | Duration |
|------|----------|
| Full brightness | ~1 hour |
| Screen off | ~3–4 hours |
| Full low-power | ~6 hours |

## I2C Device Addresses

| Device | Address |
|--------|---------|
| FT3168 touch | 0x38 |
| TCA9554 IO expander (A0/A1/A2=GND) | 0x20 |
| QMI8658 IMU (SDO=VCC) | 0x6B |
| AXP2101 PMIC | 0x34 |
| PCF85063 RTC | 0x51 |

## Pin Assignments

Pins verified against official Waveshare BSP header:
`waveshareteam/Waveshare-ESP32-components`, file
`bsp/esp32_s3_touch_amoled_1_8/include/bsp/esp32_s3_touch_amoled_1_8.h`.

| Signal | GPIO | Status |
|--------|------|--------|
| I2C SDA (shared bus) | 15 | Verified |
| I2C SCL (shared bus) | 14 | Verified |
| SH8601 QSPI CLK | 11 | Verified |
| SH8601 QSPI CS | 12 | Verified |
| SH8601 QSPI D0 | 4 | Verified |
| SH8601 QSPI D1 | 5 | Verified |
| SH8601 QSPI D2 | 6 | Verified |
| SH8601 QSPI D3 | 7 | Verified |
| LCD Reset | — | Via TCA9554 IO expander |
| Touch INT | 21 | Verified |
| Touch RST | — | Not connected |
| I2S SCLK | 9 | Verified |
| I2S MCLK | 16 | Verified |
| I2S WS (LCLK) | 45 | Verified |
| I2S DOUT | 8 | Verified |
| I2S DSIN | 10 | Verified |
| Audio AMP EN | 46 | Verified |
| microSD CLK | 2 | Verified |
| microSD CMD | 1 | Verified |
| microSD D0 | 3 | Verified |

## Development Resources

| Resource | URL |
|----------|-----|
| Official demo repo | https://github.com/waveshareteam/ESP32-S3-Touch-AMOLED-1.8 |
| Waveshare wiki | https://www.waveshare.com/wiki/ESP32-S3-Touch-AMOLED-1.8 |
| Waveshare ESP32 components | https://github.com/waveshareteam/Waveshare-ESP32-components |
| ESP32-display-support BSP | https://github.com/waveshareteam/ESP32-display-support |
| SH8601 driver (community) | https://github.com/Maucke/esp_lcd_sh8601 |
| SH8601 component registry | https://components.espressif.com/components/waveshare/esp_lcd_sh8601 |
| QMI8658 component registry | https://components.espressif.com/components/waveshare/qmi8658 |
| ESP-IDF S3 target guide | https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/ |

## Build Commands

```bash
idf.py set-target esp32s3
idf.py update-dependencies
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```
