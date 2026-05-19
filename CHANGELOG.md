# Changelog

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
