# Changelog

## 0.1.0-alpha.9

- Switched the CP8000 compiler recipe to the Boards Manager managed
  `cp8000-xuantie-elf-newlib` tool path.
- Added package-index generation for hosted compiler `tools` and
  `toolsDependencies`.
- Added toolchain archive packaging for Linux x86_64, Linux i386, macOS ARM64,
  and Windows i686/mingw.

## 0.1.0-alpha.6

- Replaced the empty platform-level `examples/` layout with seven categorized
  board-scoped example libraries: `01.GPIO`, `02.I2C_SPI`, `03.BLE`,
  `04.Serial`, `05.24GRadio`, `06.Watchdog`, and `07.OTA`.
- This layout makes the categories appear directly under
  `Examples for CHIP-PUMP CP8001 SOP16` in Arduino IDE.

## 0.1.0-alpha.5

- Moved the categorized 20 CP8000 sketches from the `CP8000Examples`
  pseudo-library into the platform-level `examples/` menu so Arduino IDE shows
  `01.GPIO`, `02.I2C_SPI`, `03.BLE`, `04.Serial`, `05.24GRadio`,
  `06.Watchdog`, and `07.OTA` directly under the CP8000 board examples.
- Removed the `CP8000Examples` pseudo-library from the package.

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
