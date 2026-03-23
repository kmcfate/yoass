# yoass

Your Only Assistant — an ESP32 application for Waveshare AMOLED touch boards.

## Supported Hardware

| Board | SoC | Display | Connectivity |
|-------|-----|---------|--------------|
| [Waveshare ESP32-C6-Touch-AMOLED-1.8](https://www.waveshare.com/esp32-c6-touch-amoled-1.8.htm) | ESP32-C6 @ 160 MHz | 1.8" AMOLED 368×448 | Wi-Fi 6, BLE 5, Zigbee, Thread |
| [Waveshare ESP32-S3-Touch-AMOLED-1.8](https://www.waveshare.com/esp32-s3-touch-amoled-1.8.htm) | ESP32-S3R8 @ 240 MHz | 1.8" AMOLED 368×448 | Wi-Fi 4, BLE 5 |

Both boards share the same peripheral stack: **SH8601** display (QSPI), **FT3168** touch (I2C),
**QMI8658** IMU, **PCF85063** RTC, **AXP2101** PMIC, and an audio codec with mic + speaker.

## Prerequisites

- [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/stable/) **v5.3 or later**
- Python 3.8+
- `idf.py` in PATH (run `. $IDF_PATH/export.sh`)

## Quick Start

### ESP32-C6 board

```bash
idf.py set-target esp32c6
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```

### ESP32-S3 board

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```

The board selection in `menuconfig` defaults automatically to the correct board for each target.
External component dependencies are resolved by the IDF Component Manager on first build.

## Project Structure

```
yoass/
├── CMakeLists.txt              # Top-level project
├── Kconfig.projbuild           # Board selection Kconfig menu
├── partitions.csv              # 16 MB flash layout
├── sdkconfig.defaults          # Shared defaults
├── sdkconfig.defaults.esp32c6  # C6-specific defaults
├── sdkconfig.defaults.esp32s3  # S3-specific defaults
├── main/
│   ├── app_main.c              # Application entry point
│   └── idf_component.yml       # External component dependencies
├── components/
│   └── board/                  # Board abstraction layer
│       ├── include/board.h     # Common API + pin definitions
│       ├── esp32_c6_amoled_1_8.c
│       └── esp32_s3_amoled_1_8.c
└── docs/hardware/
    ├── esp32-c6-amoled-1.8.md  # C6 board specifications & resources
    └── esp32-s3-amoled-1.8.md  # S3 board specifications & resources
```

## Pin Verification

Pin assignments in `components/board/include/board.h` are derived from comparable
Waveshare reference boards and are marked with `#warning` until verified against
the official schematics. See `docs/hardware/` for verification links.

## License

Apache License 2.0 — see [LICENSE](./LICENSE).
