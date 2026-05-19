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
