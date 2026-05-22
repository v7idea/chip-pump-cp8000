# Changelog

## 0.1.0-alpha.1

- Created CP8000 Arduino platform scaffold.
- Added CP8001 SOP16 and CP8003 SOP16 board definitions.
- Imported CP800X vendor SDK sources, linker scripts, and static libraries.
- Added first-pass Arduino core with GPIO, timing, Serial, ADC, PWM, I2C, SPI, watchdog, flash, sleep, BLE advertising, and 2.4G RF API surfaces.
- Added examples for basic Arduino and CP8000-specific peripherals.
- Added `cp8000-uploader` CLI and Arduino upload recipe integration.
- Added Docker-based Arduino CLI development environment.
- Added fake-toolchain CI smoke tests and package index generation.
- Added Boards Manager package archive and package index generation for
  `0.1.0-alpha.1`.
- Verified local HTTP Boards Manager install with a clean Arduino CLI data
  directory.
- Verified installed-package Blink compile with native macOS ARM XuanTie
  toolchain via `CP8000_TOOLCHAIN_PATH`.
- Hardware-validated Blink, Serial, PWM, I2C/OLED, and BLE UART during bring-up.

Known alpha limitations:

- `toolsDependencies` are not packaged yet; developers must provide a compatible
  XuanTie E902M ELF/Newlib toolchain with `CP8000_TOOLCHAIN_PATH`.
- Hardware validation from the installed Boards Manager package is still limited
  to compile/install smoke testing until the GitHub Release assets are published.
