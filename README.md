# CHIP-PUMP CP8000 Arduino SDK

Arduino Boards Manager package for CHIP-PUMP CP8000/CP800X boards.

## Boards Manager URL

Use this fixed public Boards Manager URL:

```text
https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json
```

This URL is intentionally stable. It points to the `boards-manager` GitHub
Release, whose `package_chip-pump_cp8000_index.json` asset should be replaced
whenever a new CP8000 package version is published. The package index itself
keeps previously published alpha platform versions in the same `platforms`
array, newest first.

The stable `boards-manager` asset must also be updated for any issue fix that
changes package metadata, upload recipes, platform archives, toolchain
references, or public install instructions. Do not rely only on a versioned
release asset.

The latest versioned index is also available from the release that produced it:

```text
https://github.com/v7idea/chip-pump-cp8000/releases/download/0.1.1-alpha.1/package_chip-pump_cp8000_index.json
```

## Current Package

`0.1.1-alpha.1` includes:

- CP8000 Arduino core and board definitions for CP8001 SOP16 and CP8003 SOP16.
- Board-scoped example categories:
  `01.GPIO`, `02.I2C_SPI`, `03.BLE`, `04.Serial`, `05.24GRadio`,
  `06.Watchdog`, and `07.OTA`.
- CP8xxx UART uploader integration, including the Windows `.cmd` launcher recipe.
- Vendor CP8000 runtime libraries and linker assets required by the examples.
- Boards Manager managed XuanTie ELF/Newlib compiler packages.

## Toolchain Packages

Arduino IDE / Arduino CLI downloads `cp8000-xuantie-elf-newlib@0.1.0-alpha.9`
automatically through the `0.1.1-alpha.1` platform `toolsDependencies`.

Packaged hosts:

- `x86_64-linux-gnu`: vendor XuanTie ELF/Newlib V3.4.0 x86_64 compiler.
- `i686-linux-gnu`: vendor XuanTie ELF/Newlib V3.4.0 i386 compiler.
- `arm64-apple-darwin`: native macOS ARM XuanTie/Newlib compiler build.
- `i686-mingw32`: vendor XuanTie ELF/Newlib V3.4.0 Windows compiler.

The Windows package is a PE32 i386 executable bundle, so the Arduino host is
`i686-mingw32`.

## Arduino CLI Install

```bash
arduino-cli core update-index \
  --additional-urls https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json

arduino-cli core install chippump:cp8000@0.1.1-alpha.1 \
  --additional-urls https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json
```

Compile Blink:

```bash
arduino-cli compile \
  --fqbn chippump:cp8000:cp8001_sop16 \
  arduino/hardware/chippump/cp8000/libraries/01.GPIO/examples/Blink
```

## Windows IDE Refresh

If Arduino IDE on Windows does not show the latest CP8000 package after a
release:

1. Close Arduino IDE.
2. Open:

   ```text
   C:\Users\<USER>\AppData\Local\Arduino15
   ```

3. Delete cached CP8000 package indexes and downloads:

   ```text
   package_chip-pump_cp8000_index.json
   package_chip-pump_cp8000_index.json.sig
   staging\packages\chippump-cp8000-*.tar.gz
   ```

4. Reopen Arduino IDE.
5. Confirm this URL is in Additional Boards Manager URLs:

   ```text
   https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json
   ```

6. Open Boards Manager, search `CP8000`, and select the newest version from the
   version dropdown.

For command-line verification on Windows:

```powershell
arduino-cli core update-index --additional-urls "https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json"
arduino-cli core search cp8000 --additional-urls "https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json"
```

## Release Packaging

Generate the platform archive, toolchain archives, and package index:

```bash
make package-tools
make index
```

Release assets expected by Boards Manager for `0.1.1-alpha.1`:

- `package_chip-pump_cp8000_index.json`
- `chippump-cp8000-0.1.1-alpha.1.tar.gz`
- `cp8000-xuantie-elf-newlib-0.1.0-alpha.9-x86_64-linux-gnu.tar.gz`
- `cp8000-xuantie-elf-newlib-0.1.0-alpha.9-i686-linux-gnu.tar.gz`
- `cp8000-xuantie-elf-newlib-0.1.0-alpha.9-arm64-apple-darwin.tar.gz`
- `cp8000-xuantie-elf-newlib-0.1.0-alpha.9-i686-mingw32.tar.gz`

`0.1.1-alpha.1` changes only the platform uploader recipe and reuses the
`0.1.0-alpha.9` toolchain package through `toolsDependencies`. The patch is
released under `0.1.1-alpha.1` rather than `0.1.0-alpha.10` so Arduino IDE
version sorting on Windows clearly treats it as newer than `0.1.0-alpha.9`.

After publishing a versioned release, update the stable Boards Manager release:

```bash
gh release upload boards-manager package/package_chip-pump_cp8000_index.json \
  --repo v7idea/chip-pump-cp8000 --clobber
```

## Notes

This package is an alpha release for hardware bring-up and Arduino ecosystem
validation. The API surface is still moving, especially BLE, OTA, and production
flashing workflows.
