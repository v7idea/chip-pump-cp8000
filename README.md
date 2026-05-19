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
