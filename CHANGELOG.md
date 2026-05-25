# Changelog

## 0.1.1

- Promoted the current CP8000 Arduino Boards Manager package to the first
  `0.1.1` release.
- Kept the reset or power-cycle upload reminder before serial bootloader
  connection attempts.
- Added multilingual public install guide pages and Windows Boards Manager
  cache cleanup guidance.
- Fixed package-index version sorting so stable releases sort above matching
  prerelease builds.

## 0.1.1-alpha.4

- Added first-run `pyserial` auto-install for uploader commands that need a
  serial port, using the same Python interpreter launched by Arduino IDE.
- Kept manual setup guidance and added `CP8000_UPLOADER_AUTO_INSTALL=0` as an
  opt-out for managed/offline Python environments.

## 0.1.1-alpha.3

- Added clear `pyserial` setup guidance for Windows, macOS, and Linux upload
  failures.
- Made the uploader catch missing `pyserial` during upload and port listing so
  Arduino IDE users see install commands instead of a Python traceback.
- Documented the Python uploader dependency in the public Arduino CLI install
  instructions.

## 0.1.1-alpha.2

- Fixed Windows Arduino IDE upload invocation by calling the packaged
  `cp8000-uploader.cmd` directly instead of wrapping it in `cmd /C`.
- Made the Arduino upload recipe explicitly pass the validated CP8xxx flash
  flow: `prelude-sync`, manual boot reset, cached flash helper, self-start, and
  vendor run address `0x20002000`.
- Improved the Windows launcher to find `py -3`, `python3`, or `python`, and
  print a clear Python setup error when no interpreter is available.

## 0.1.1-alpha.1

- Fixed Windows Arduino IDE upload by using the packaged
  `cp8000-uploader.cmd` launcher through a Windows-specific upload recipe
  instead of referencing a missing `cp8000-uploader.exe`.
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
