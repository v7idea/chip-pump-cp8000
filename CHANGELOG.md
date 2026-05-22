# Changelog

## 0.1.0-alpha.4

- Grouped the 20 `CP8000Examples` sketches into Arduino IDE categories:
  `01.GPIO`, `02.I2C_SPI`, `03.BLE`, `04.Serial`, `05.24GRadio`,
  `06.Watchdog`, and `07.OTA`.

## 0.1.0-alpha.3

- Added `CP8000Examples` so Arduino IDE and Arduino CLI list the planned 20 CP8000 examples from Boards Manager installations.
- Improved uploader diagnostics when Arduino IDE selects a stale or missing serial port.
- Updated package generation to suppress macOS AppleDouble `._*` files in release archives.

## 0.1.0-dev

- Created CP8000 Arduino platform scaffold.
- Added CP8001 SOP16 and CP8003 SOP16 board definitions.
- Imported CP800X vendor SDK sources, linker scripts, and static libraries.
- Added first-pass Arduino core with GPIO, timing, Serial, ADC, PWM, I2C, SPI, watchdog, flash, sleep, BLE advertising, and 2.4G RF API surfaces.
- Added examples for basic Arduino and CP8000-specific peripherals.
- Added `cp8000-uploader` CLI scaffold and Arduino upload recipe integration.
- Added Docker-based Arduino CLI development environment.
- Added fake-toolchain CI smoke tests and package index generation.

Known blockers:

- Real E902M toolchain is not available in this repository.
- UART bootloader protocol is not implemented.
- Vendor SDK/toolchain redistribution license is not confirmed.
- Hardware validation has not been completed.
