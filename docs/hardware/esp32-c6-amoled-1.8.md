# Waveshare ESP32-C6-Touch-AMOLED-1.8

## Overview

Compact 1.8-inch AMOLED development board based on the ESP32-C6 RISC-V SoC.
Integrates display, touch, IMU, RTC, PMIC, IO expander, and audio peripherals.

## Specifications

| Feature | Detail |
|---------|--------|
| **SoC** | ESP32-C6, RISC-V 32-bit single-core |
| **CPU speed** | Up to 160 MHz |
| **Flash** | 16 MB (external, QIO) |
| **RAM** | 512 KB HP SRAM + 16 KB LP SRAM (internal) |
| **PSRAM** | None |
| **Wi-Fi** | 802.11ax (Wi-Fi 6), 2.4 GHz, onboard antenna |
| **Bluetooth** | BLE 5 |
| **IEEE 802.15.4** | Zigbee 3.0 + Thread (concurrent with Wi-Fi/BT) |
| **Display** | 1.8" AMOLED, 368 × 448 px, 16.7 M colors |
| **Display driver** | SH8601, QSPI interface |
| **Touch** | FT3168 or FT6146, I2C interface |
| **IO expander** | TCA9554, I2C (controls LCD reset and power rails) |
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
| TCA9554 IO expander (A0/A1/A2=GND) | 0x20 |
| QMI8658 IMU (SDO=VCC) | 0x6B |
| AXP2101 PMIC | 0x34 |
| PCF85063 RTC | 0x51 |

## Pin Assignments

Pins verified against official Waveshare demo repository:
`waveshareteam/ESP32-C6-Touch-AMOLED-1.8`, examples `05_LVGL_WITH_RAM` and `01_AXP2101`.

| Signal | GPIO | Status |
|--------|------|--------|
| I2C SDA (shared bus) | 8 | Verified |
| I2C SCL (shared bus) | 7 | Verified |
| SH8601 QSPI CLK | 0 | Verified |
| SH8601 QSPI CS | 5 | Verified |
| SH8601 QSPI D0 | 1 | Verified |
| SH8601 QSPI D1 | 2 | Verified |
| SH8601 QSPI D2 | 3 | Verified |
| SH8601 QSPI D3 | 4 | Verified |
| LCD Reset | — | Via TCA9554 IO expander |
| Touch INT | 15 | Verified |
| Touch RST | — | Not connected |
| I2S SCLK | 3 | **VERIFY** — may conflict with QSPI D2 |
| I2S MCLK | 15 | **VERIFY** |
| I2S WS | 5 | **VERIFY** — may conflict with QSPI CS |
| I2S DOUT | 6 | **VERIFY** |
| I2S DSIN | 4 | **VERIFY** — may conflict with QSPI D3 |

> Audio pins are derived from the related ESP32-C6 1.32" BSP variant, not the 1.8" schematic directly.
> Verify against the physical schematic before enabling audio.
> QSPI and audio cannot be used simultaneously on the same GPIO lines.

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
idf.py set-target esp32c6
idf.py update-dependencies
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```
