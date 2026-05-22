# CHIP-PUMP CP8000 Arduino SDK

Arduino Boards Manager package for CHIP-PUMP CP8000/CP800X boards.

## Boards Manager URL

Use the versioned package index URL:

```text
https://github.com/v7idea/chip-pump-cp8000/releases/download/0.1.0-alpha.8/package_chip-pump_cp8000_index.json
```

The package index keeps previously published alpha platform versions in the
same `platforms` array, newest first.

## Current Package

`0.1.0-alpha.8` includes:

- CP8000 Arduino core and board definitions for CP8001 SOP16 and CP8003 SOP16.
- Board-scoped example categories:
  `01.GPIO`, `02.I2C_SPI`, `03.BLE`, `04.Serial`, `05.24GRadio`,
  `06.Watchdog`, and `07.OTA`.
- CP8xxx UART uploader integration.
- Vendor CP8000 runtime libraries and linker assets required by the examples.
- Boards Manager managed XuanTie ELF/Newlib compiler packages.

## Toolchain Packages

Starting with `0.1.0-alpha.8`, Arduino IDE / Arduino CLI downloads the
`cp8000-xuantie-elf-newlib` tool automatically through `toolsDependencies`.

Packaged hosts:

- `x86_64-linux-gnu`: vendor XuanTie ELF/Newlib V3.4.0 x86_64 compiler.
- `i686-linux-gnu`: vendor XuanTie ELF/Newlib V3.4.0 i386 compiler.
- `arm64-apple-darwin`: native macOS ARM XuanTie/Newlib compiler build.

Windows is pending because the current SDK set does not include a
redistributable Windows XuanTie ELF/Newlib compiler bundle containing
`riscv64-unknown-elf-gcc.exe`.

## Arduino CLI Install

```bash
arduino-cli core update-index \
  --additional-urls https://github.com/v7idea/chip-pump-cp8000/releases/download/0.1.0-alpha.8/package_chip-pump_cp8000_index.json

arduino-cli core install chippump:cp8000@0.1.0-alpha.8 \
  --additional-urls https://github.com/v7idea/chip-pump-cp8000/releases/download/0.1.0-alpha.8/package_chip-pump_cp8000_index.json
```

Compile Blink:

```bash
arduino-cli compile \
  --fqbn chippump:cp8000:cp8001_sop16 \
  arduino/hardware/chippump/cp8000/libraries/01.GPIO/examples/Blink
```

## Release Packaging

Generate the platform archive, toolchain archives, and package index:

```bash
make package-tools
make index
```

Release assets expected by Boards Manager:

- `package_chip-pump_cp8000_index.json`
- `chippump-cp8000-0.1.0-alpha.8.tar.gz`
- `cp8000-xuantie-elf-newlib-0.1.0-alpha.8-x86_64-linux-gnu.tar.gz`
- `cp8000-xuantie-elf-newlib-0.1.0-alpha.8-i686-linux-gnu.tar.gz`
- `cp8000-xuantie-elf-newlib-0.1.0-alpha.8-arm64-apple-darwin.tar.gz`

## Notes

This package is an alpha release for hardware bring-up and Arduino ecosystem
validation. The API surface is still moving, especially BLE, OTA, and production
flashing workflows.
