# CHIP-PUMP CP8000 Arduino Package

Public release workspace for the CP8000/CP800X Arduino SDK.

This repository contains the public-safe subset of the private
`Arduino-CP8000-Develop` development repository. The private repository keeps
this GitHub repository as a submodule and syncs selected files into it.

Day-to-day development still happens privately in Azure DevOps. Public release
preparation happens here.

For an Arduino Boards Manager public release, the generated package archive and
`package_chip-pump_cp8000_index.json` must be hosted at public URLs. Arduino IDE
users should not need Azure DevOps access.

## Current Public Export

The first public export intentionally excludes files whose redistribution rights
still need confirmation:

- vendor SDK source under `arduino/hardware/chippump/cp8000/system/sdk`
- vendor static libraries under `arduino/hardware/chippump/cp8000/system/libs`
- vendor flash algorithm ELF files
- hosted toolchain binaries
- generated build and package archives

Until those items are cleared for redistribution, this repository is a public
source and release-preparation workspace, not yet a complete installable Boards
Manager package.

## Current Compile Status

The current completed example set compiles with the native macOS ARM XuanTie
toolchain from a no-space working copy: 20/20 examples passed, including Blink,
Serial, ADC, PWM, Wire/OLED, SPI, BLE, RF24G, Flash, Watchdog, and Sleep
sketches. Blink was also uploaded with the CP8xxx uploader and hardware
validated with LED Blink.

For Apple Silicon Macs, Docker `linux/amd64` plus the Linux x86_64 XuanTie
ELF/Newlib toolchain remains the official stable release compile path. Native
macOS ARM is available as an experimental developer path until more examples
are hardware-validated and the Arduino CLI path-with-spaces issue is resolved.

Toolchain host status:

- Linux x86_64: verified with `Xuantie-900-gcc-elf-newlib-x86_64-V3.4.0`.
- Linux i386/x86: discovered locally, but not the active validated path.
- native macOS ARM: built from `XUANTIE-RV/xuantie-gnu-toolchain` `V3.0.1`,
  compiles 20/20 completed examples, and runs Blink on hardware.

## Clone

```bash
git clone https://github.com/v7idea/chip-pump-cp8000.git
cd chip-pump-cp8000
```

No private submodule access is required for the public clone.

## Local Smoke Checks

```bash
make smoke
make package
make index
```

The package commands are expected to become release-ready after the vendor file
redistribution decision is resolved.

For real native macOS ARM compiler probing:

```bash
CP8000_TOOLCHAIN_PATH=/tmp/cp8000-xuantie-build/install \
scripts/probe_macos_arm_toolchain.sh
```

## Boards Manager MVP

The first Boards Manager MVP should prove that a public user can install,
compile, and upload without Azure DevOps access.

MVP definition:

- A GitHub Release publishes `package_chip-pump_cp8000_index.json`.
- The package index uses real GitHub release asset URLs, not
  `example.invalid`.
- The platform archive downloads publicly and extracts into a valid Arduino
  platform containing `boards.txt`, `platform.txt`, `programmers.txt`, `cores`,
  `variants`, `libraries`, `tools`, `system/linker`, and any redistributable
  runtime assets.
- Arduino IDE can install `CHIP-PUMP CP8000 Boards` through Additional Boards
  Manager URLs.
- Arduino CLI can install the same package with
  `arduino-cli core install chippump:cp8000`.
- Blink compiles and uploads to CP8001 SOP16 from the installed package.
- The completed example set compiles from the installed package on the stable
  Docker `linux/amd64` path.
- At least Blink, Serial, PWM, Wire/OLED, and BLE UART are hardware-validated
  from the installed package.

Non-goals for the first MVP:

- Arduino Library Manager publication.
- OTA update flow.
- Full CP800X package matrix.
- Replacing the stable Docker x86_64 toolchain path with native macOS ARM.
- Publishing vendor files before redistribution permission is confirmed.

## Boards Manager TODO

- [ ] Replace `example.invalid` metadata in
      `package/package_chip-pump_cp8000_index.json` and
      `scripts/generate_package_index.py`.
- [ ] Choose package metadata:
      `name=chippump`, platform architecture `cp8000`, maintainer name,
      support email, website URL, and help URL.
- [ ] Decide release version format. Use Arduino-compatible semver such as
      `0.1.0-alpha.1`, then keep `platform.txt`, archive name, GitHub tag, and
      package index version aligned.
- [ ] Confirm redistribution rights for vendor SDK source, static libraries,
      flash algorithm files, uploader assets, and XuanTie toolchains.
- [ ] Package host tool dependencies in the package index if redistribution is
      allowed. Required hosts to plan for: `x86_64-linux-gnu`,
      `i686-linux-gnu`, `x86_64-mingw32`, `i686-mingw32`,
      `x86_64-apple-darwin`, and `arm64-apple-darwin`.
- [ ] If toolchain redistribution is not allowed, document the manual
      `CP8000_TOOLCHAIN_PATH` installation flow and keep the package marked as
      developer preview.
- [ ] Replace local wrapper-only toolchain behavior with release-safe
      `toolsDependencies` entries or a documented manual toolchain path.
- [ ] Ensure `tools/cp8000-uploader` packages binaries for macOS, Linux, and
      Windows, or provide a portable Python/package strategy accepted by
      Arduino CLI.
- [ ] Run package generation:
      `scripts/package_platform.sh <version>`.
- [ ] Generate package index with the final GitHub release asset URL and verify
      SHA-256 checksum and size.
- [ ] Create a GitHub Release and upload the platform archive plus package
      index.
- [ ] Test Arduino CLI install using a clean data directory:
      `arduino-cli core update-index --additional-urls <index-url>`.
- [ ] Test Arduino IDE install using Additional Boards Manager URLs.
- [ ] Compile installed examples: Blink, CoreHelpers, SerialEcho,
      SerialAdvanced, AnalogReadSerial, Fade, I2CScanner, OLED128x64I2C,
      SPITransfer, WatchdogReset, FlashUID, SleepTimed, BLE examples, and
      RF24GSend.
- [ ] Upload hardware tests from the installed package: Blink, SerialEcho,
      Fade, OLED128x64I2C, and BLEUartEcho.
- [ ] Add GitHub Actions to build the archive, regenerate the index, upload
      release assets, and run recipe smoke checks.
- [ ] Add a release checklist that blocks public announcement until install,
      compile, upload, and hardware smoke tests pass.

## Required Arduino Settings

Package index settings:

- File name: `package_chip-pump_cp8000_index.json`.
- Public URL:
  `https://github.com/v7idea/chip-pump-cp8000/releases/latest/download/package_chip-pump_cp8000_index.json`.
- Package name: `chippump`; this becomes the vendor folder under Arduino
  packages.
- Platform architecture: `cp8000`; the FQBN is currently
  `chippump:cp8000:cp8001_sop16`.
- Platform archive format: keep `.tar.gz` for compatibility with older Arduino
  IDE and Arduino CLI versions.
- `url`, `archiveFileName`, `checksum`, and `size` must match the uploaded
  GitHub release archive exactly.
- `toolsDependencies` must either list every hosted compiler/uploader tool
  needed by the package or remain empty only for a developer-preview flow that
  documents manual local toolchain setup.

Platform settings:

- `platform.txt` must keep compiler recipes for C, C++, assembly, archive,
  link, objcopy, size, and upload.
- `platform.txt` upload recipe must call `cp8000-uploader` with the CP8xxx
  binary protocol and the correct flash base.
- `boards.txt` must expose CP8001 SOP16 and CP8003 SOP16 board IDs, upload
  targets, maximum flash/SRAM sizes, `build.mcu=e902m`, `build.f_cpu`, variants,
  and menu options.
- `programmers.txt` can remain minimal unless burn-bootloader or production
  programming is added.
- `variants/*/pins_arduino.h` must keep stable Arduino pin aliases for examples
  and user sketches.

User install settings:

- Arduino IDE: open Settings/Preferences, add the package index URL under
  Additional Boards Manager URLs, then install `CHIP-PUMP CP8000 Boards`.
- Arduino CLI:

```bash
arduino-cli config add board_manager.additional_urls \
  https://github.com/v7idea/chip-pump-cp8000/releases/latest/download/package_chip-pump_cp8000_index.json
arduino-cli core update-index
arduino-cli core install chippump:cp8000
arduino-cli compile --fqbn chippump:cp8000:cp8001_sop16 examples/Blink
arduino-cli upload -p /dev/cu.usbserial-XXXX --fqbn chippump:cp8000:cp8001_sop16 examples/Blink
```

## Sync Source

This repository is synced from the private development repository with:

```text
scripts/sync_public_repo.sh chip-pump-cp8000
```

## Boards Manager Goal

The final public URL should be usable in Arduino IDE:

```text
https://github.com/v7idea/chip-pump-cp8000/releases/latest/download/package_chip-pump_cp8000_index.json
```

This URL is the intended direction. It should only be published after the
release workflow uploads the package index and archive assets, and after a clean
Arduino IDE install test passes.
