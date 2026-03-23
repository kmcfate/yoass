# Waveshare ESP32-S3-Touch-AMOLED-1.8

## Overview

Compact 1.8-inch AMOLED development board based on the ESP32-S3R8 SoC.
Adds 8 MB stacked octal PSRAM and a microSD card slot compared to the C6 variant,
while sharing the same display, touch, IMU, RTC, and PMIC peripherals.

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
| QMI8658 IMU (SDO low) | 0x6A |
| AXP2101 PMIC | 0x34 |
| PCF85063 RTC | 0x51 |

## Pin Assignments

> **Important:** The pin values below are based on comparable Waveshare S3 AMOLED
> board schematics. Verify every entry against the official schematic and demo
> source before flashing real hardware.

| Signal | GPIO | Notes |
|--------|------|-------|
| I2C SDA | 6 | Shared by touch, IMU, RTC, PMIC |
| I2C SCL | 7 | Shared by touch, IMU, RTC, PMIC |
| SH8601 QSPI CLK | 47 | Verify |
| SH8601 QSPI CS | 9 | Verify |
| SH8601 QSPI D0 | 18 | Verify |
| SH8601 QSPI D1 | 17 | Verify |
| SH8601 QSPI D2 | 16 | Verify |
| SH8601 QSPI D3 | 15 | Verify |
| LCD Reset | — | Controlled via AXP2101 PMIC |
| Touch INT | — | Verify if connected |
| microSD CLK | 12 | Verify |
| microSD CMD | 11 | Verify |
| microSD D0 | 13 | Verify |

Update `components/board/include/board.h` once confirmed.

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
# One-time setup
idf.py set-target esp32s3

# Configure (board auto-selected by target)
idf.py menuconfig

# Build, flash, monitor
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```
