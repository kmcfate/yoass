# Waveshare ESP32-C6-Touch-AMOLED-1.8

## Overview

Compact 1.8-inch AMOLED development board based on the ESP32-C6 RISC-V SoC.
Integrates display, touch, IMU, RTC, PMIC, and audio peripherals in a single module.

## Specifications

| Feature | Detail |
|---------|--------|
| **SoC** | ESP32-C6, RISC-V 32-bit single-core |
| **CPU speed** | Up to 160 MHz |
| **Flash** | 16 MB (external, QIO) |
| **RAM** | 512 KB HP SRAM + 16 KB LP SRAM (internal) |
| **PSRAM** | None |
| **Wi-Fi** | 802.11 ax (Wi-Fi 6), 2.4 GHz, onboard antenna |
| **Bluetooth** | BLE 5 |
| **IEEE 802.15.4** | Zigbee 3.0 + Thread (concurrent with Wi-Fi/BT) |
| **Display** | 1.8" AMOLED, 368 × 448 px, 16.7 M colors |
| **Display driver** | SH8601, QSPI interface |
| **Touch** | FT3168 or FT6146, I2C interface |
| **IMU** | QMI8658, 6-axis (±2/4/8/16 g accel + ±16–2048 °/s gyro) |
| **RTC** | PCF85063, backup battery pads onboard |
| **PMIC** | AXP2101 (LiPo charge/discharge + rail management) |
| **Audio** | Low-power audio codec, built-in microphone, speaker header |
| **Expansion** | 11 × solderable pads (USB, UART, I2C, BAT, 5 V, 3.3 V, GND), 1.5 mm pitch |
| **USB** | Type-C (power + programming) |
| **Battery** | 3.7 V LiPo via MX1.25 header (optional) |

## I2C Device Addresses

| Device | Address |
|--------|---------|
| FT3168 touch | 0x38 |
| QMI8658 IMU (SDO low) | 0x6A |
| AXP2101 PMIC | 0x34 |
| PCF85063 RTC | 0x51 |

## Pin Assignments

> **Important:** The pin values below are placeholders derived from similar
> Waveshare C6 boards. Verify every entry against the official schematic and
> demo source before flashing real hardware.

| Signal | GPIO | Notes |
|--------|------|-------|
| I2C SDA | 6 | Shared by touch, IMU, RTC, PMIC |
| I2C SCL | 7 | Shared by touch, IMU, RTC, PMIC |
| SH8601 QSPI CLK | 1 | Verify |
| SH8601 QSPI CS | 2 | Verify |
| SH8601 QSPI D0 | 3 | Verify |
| SH8601 QSPI D1 | 4 | Verify |
| SH8601 QSPI D2 | 5 | Verify |
| SH8601 QSPI D3 | 10 | Verify |
| LCD Reset | — | Controlled via AXP2101 PMIC |
| Touch INT | — | Verify if connected |

Update `components/board/include/board.h` once confirmed.

## Development Resources

| Resource | URL |
|----------|-----|
| Official demo repo | https://github.com/waveshareteam/ESP32-C6-Touch-AMOLED-1.8 |
| Waveshare wiki | https://www.waveshare.com/wiki/ESP32-C6-Touch-AMOLED-1.8 |
| Waveshare docs | https://docs.waveshare.com/ESP32-C6-Touch-AMOLED-1.8 |
| Waveshare ESP32 components | https://github.com/waveshareteam/Waveshare-ESP32-components |
| ESP32-display-support BSP | https://github.com/waveshareteam/ESP32-display-support |
| SH8601 component registry | https://components.espressif.com/components/waveshare/esp_lcd_sh8601 |
| QMI8658 component registry | https://components.espressif.com/components/waveshare/qmi8658 |
| ESP-IDF C6 target guide | https://docs.espressif.com/projects/esp-idf/en/stable/esp32c6/ |

## Build Commands

```bash
# One-time setup
idf.py set-target esp32c6

# Configure (board auto-selected by target)
idf.py menuconfig

# Build, flash, monitor
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```
