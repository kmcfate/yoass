# CLAUDE.md

This file provides guidance for AI assistants (e.g., Claude Code) working in this repository.

## Project Overview

**yoass** (Your Only Assistant) is an **ESP-IDF v5.3+ application** targeting two
Waveshare 1.8-inch AMOLED touch development boards:

- **ESP32-C6-Touch-AMOLED-1.8** — RISC-V 32-bit @ 160 MHz, Wi-Fi 6, BLE 5, Zigbee 3.0, Thread
- **ESP32-S3-Touch-AMOLED-1.8** — LX7 dual-core @ 240 MHz, Wi-Fi 4, BLE 5, 8 MB PSRAM

Both boards use identical peripheral ICs:
SH8601 display (QSPI), FT3168 touch (I2C), QMI8658 IMU (I2C), PCF85063 RTC (I2C),
AXP2101 PMIC (I2C), audio codec + mic + speaker.

## Repository Structure

```
yoass/
├── CMakeLists.txt              # Top-level ESP-IDF project
├── Kconfig.projbuild           # Board selection menu (YOASS_BOARD)
├── partitions.csv              # 16 MB custom flash partition table
├── sdkconfig.defaults          # Shared sdkconfig (both targets)
├── sdkconfig.defaults.esp32c6  # C6-specific: QIO flash, no PSRAM
├── sdkconfig.defaults.esp32s3  # S3-specific: QIO flash, octal PSRAM
├── .gitignore                  # Excludes build/, sdkconfig, managed_components/
├── main/
│   ├── CMakeLists.txt
│   ├── idf_component.yml       # IDF Component Manager dependencies
│   └── app_main.c              # Entry point — calls board_init()
├── components/
│   └── board/                  # Board abstraction layer
│       ├── CMakeLists.txt
│       ├── include/board.h     # board_init(), pin macros, LCD dimensions
│       ├── esp32_c6_amoled_1_8.c  # C6 I2C/QSPI/LVGL init (compiled when C6 target)
│       └── esp32_s3_amoled_1_8.c  # S3 I2C/QSPI/LVGL init (compiled when S3 target)
└── docs/
    └── hardware/
        ├── esp32-c6-amoled-1.8.md  # C6 full spec + pin table + resource links
        └── esp32-s3-amoled-1.8.md  # S3 full spec + pin table + resource links
```

## Build System

This is a standard **ESP-IDF CMake project**. The IDF Component Manager (`idf_component.yml`)
fetches all external components automatically on first build.

### Selecting a target board

```bash
idf.py set-target esp32c6    # Waveshare ESP32-C6-Touch-AMOLED-1.8
idf.py set-target esp32s3    # Waveshare ESP32-S3-Touch-AMOLED-1.8
```

`sdkconfig.defaults.<target>` is merged automatically. The `Kconfig.projbuild`
board selection defaults to the correct board for each IDF target.

### Common commands

```bash
idf.py menuconfig            # Review/change configuration
idf.py build                 # Compile
idf.py -p PORT flash monitor # Flash and open serial monitor
idf.py fullclean             # Remove build/ and sdkconfig
```

### Adding a component dependency

```bash
idf.py add-dependency "namespace/component_name>=version"
# This updates main/idf_component.yml and fetches on next build.
```

## External Dependencies (idf_component.yml)

| Component | Version | Purpose |
|-----------|---------|---------|
| `waveshare/esp_lcd_sh8601` | >=1.0.2 | SH8601 AMOLED display driver (QSPI) |
| `waveshare/qmi8658` | >=1.0.1 | QMI8658 6-axis IMU |
| `espressif/esp_lcd_touch_ft5x06` | >=1.0.0 | FT3168/FT6146 touch (I2C) |
| `espressif/esp_lvgl_port` | >=2.3.0 | LVGL double-buffered port |
| `lvgl/lvgl` | ~9.2.0 | LVGL graphics library |

AXP2101 PMIC support: add `lewisxhe/xpowerslib` when available on the registry,
or vendor the driver from [Waveshare-ESP32-components](https://github.com/waveshareteam/Waveshare-ESP32-components).

## Board Abstraction Layer (`components/board/`)

`board_init()` (declared in `board.h`) is the single entry point for all hardware setup.
It initialises I2C, PMIC, display, touch, IMU, RTC, and LVGL in order.

Board-specific source files are compiled unconditionally but are wrapped in
`#if CONFIG_YOASS_BOARD_ESP32_C6_AMOLED_1_8` / `#if CONFIG_YOASS_BOARD_ESP32_S3_AMOLED_1_8`
guards so only the relevant target compiles.

Pin assignments in `board.h` are marked with `#warning` where they require
schematic verification. Always check `docs/hardware/` for the verification
checklist and authoritative resource links before flashing physical hardware.

## Key Constants

| Macro | Value | Meaning |
|-------|-------|---------|
| `BOARD_LCD_H_RES` | 368 | Display horizontal pixels |
| `BOARD_LCD_V_RES` | 448 | Display vertical pixels |
| `BOARD_I2C_ADDR_TOUCH` | 0x38 | FT3168 I2C address |
| `BOARD_I2C_ADDR_IMU` | 0x6A | QMI8658 I2C address (SDO low) |
| `BOARD_I2C_ADDR_PMIC` | 0x34 | AXP2101 I2C address |
| `BOARD_I2C_ADDR_RTC` | 0x51 | PCF85063 I2C address |

## Branches

- `master` / `main` — primary branch
- Feature branches follow the pattern `claude/<description>-<id>`

## Conventions

- Never commit `sdkconfig`, `build/`, `managed_components/`, or `dependencies.lock`
- Secrets (Wi-Fi credentials, API keys) go in `sdkconfig` at runtime — never in source
- All new peripheral drivers belong in `components/`; application logic in `main/`
- Update `docs/hardware/` whenever pin assignments are confirmed from schematic

## License

Apache License 2.0 — see [LICENSE](./LICENSE).
