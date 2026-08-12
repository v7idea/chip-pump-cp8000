# CHIP-PUMP CP8000 Arduino SDK

Languages: [English](README.md) | [繁體中文](README.zh-TW.md) | [简体中文](README.zh-CN.md) | [日本語](README.ja.md)

Arduino Boards Manager package for CHIP-PUMP CP8000/CP800X boards.

Visual Arduino IDE install guide: [English](install-board-sdk.en.html) |
[繁體中文](install-board-sdk.html) |
[简体中文](install-board-sdk.zh-CN.html) |
[日本語](install-board-sdk.ja.html)

## Boards Manager URL

Use this fixed public Boards Manager URL:

```text
https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json
```

The URL is intentionally stable. Public install instructions should point to
this `boards-manager` release asset, not to a versioned package index.

## Requirements

- Arduino IDE 2.x or Arduino CLI.
- Internet access during first install so Arduino can download the CP8000
  platform and XuanTie toolchain packages.
- Python 3.9 or newer available on `PATH`.
- `pip` for that Python installation.
- USB-to-UART driver for your adapter or board.

The CP8000 uploader uses Python `pyserial` for serial-port access. Starting in
`0.1.6`, uploader commands that need a serial port check for
`pyserial` and try to install it automatically with the same Python interpreter:

```bash
python -m pip install --user --disable-pip-version-check --no-input "pyserial>=3.5"
```

For managed or offline Python environments, disable automatic install with:

```bash
CP8000_UPLOADER_AUTO_INSTALL=0
```

Manual install commands:

```powershell
py -3 -m pip install pyserial
```

```bash
python3 -m pip install pyserial
```

## Arduino IDE Install

1. Open Arduino IDE.
2. Open **File > Preferences**.
3. Add the Boards Manager URL above to **Additional Boards Manager URLs**.
4. Open **Tools > Board > Boards Manager**.
5. Search `CP8000`.
6. Install `CHIP-PUMP CP8000 Boards`.
7. Select a board such as **CP81-Mini**.
8. Select the correct serial port and upload an example.

### Automatic Upload Reset

`Tools > Auto Upload Reset > Enabled` is the default. Firmware built with this
option includes a small Core listener on the UART0 upload pins at 115200 baud.
On the next upload, the uploader asks the running firmware to acknowledge and
perform a software reset, then confirms when the ROM bootloader responds.

The first upload from older firmware still needs the physical Reset button.
Manual Reset is also the fallback when a sketch is stalled or sleeping, stops
servicing Core polling, or changes UART0 to a baud other than 115200. The sketch
does not need to define its own reset handler.

This flow has been hardware-validated with a CH340 USB-to-TTL adapter. An old
firmware image correctly required the manual Reset fallback; after installing
the updated Core, the next upload received the application reset ACK followed
by the ROM bootloader ACK and completed without pressing Reset.

### Windows Boards Manager Cache

Arduino IDE on Windows can keep an old Boards Manager package index even after
the public URL has been updated. If Boards Manager only shows an older CP8000
version, for example `0.1.0-alpha.9`, or does not show the latest release, close
Arduino IDE and clear only the CP8000-related cache files under:

```text
C:\Users\<USER>\AppData\Local\Arduino15
```

Files that may need to be removed:

```text
package_chip-pump_cp8000_index.json
package_chip-pump_cp8000_index.json.sig
staging\packages\chippump-cp8000-*.tar.gz
```

PowerShell example:

```powershell
$arduino15 = Join-Path $env:LOCALAPPDATA "Arduino15"
Remove-Item "$arduino15\package_chip-pump_cp8000_index.json" -ErrorAction SilentlyContinue
Remove-Item "$arduino15\package_chip-pump_cp8000_index.json.sig" -ErrorAction SilentlyContinue
Remove-Item "$arduino15\staging\packages\chippump-cp8000-*.tar.gz" -ErrorAction SilentlyContinue
```

Do not delete the whole `Arduino15` directory unless you intentionally want to
remove all installed board packages and caches. After clearing the CP8000 cache,
reopen Arduino IDE, verify the Additional Boards Manager URL, and check the
Boards Manager version dropdown again.

## Arduino CLI Install

```bash
arduino-cli core update-index \
  --additional-urls https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json

arduino-cli core install chippump:cp8000@0.1.6 \
  --additional-urls https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json
```

Compile Blink:

```bash
arduino-cli compile \
  --fqbn chippump:cp8000:cp8001_sop16 \
  arduino/hardware/chippump/cp8000/libraries/01.GPIO/examples/Blink
```

## BLE OTA Examples

`07.OTA` now includes `BLEOTADevice`, `BLEOTAHostSender`, and
`BLEOTABootloader`.

- Build `BLEOTADevice` with **Tools > OTA Mode > BLE OTA Device App**. This
  compiles the application for flash address `0x10001000` and enables the
  vendor BLE OTA service.
- `BLEOTAHostSender` includes `send_ota.py`, a computer-side BLE sender:
  `python3 -m pip install bleak`, then
  `python3 send_ota.py firmware.bin --name CP8000-OTA`.
- `BLEOTABootloader` documents the required bootloader role. A real OTA setup
  must first place a minimal OTA bootloader at `0x10000000`; the OTA
  application is then transferred over BLE into the app slot.

## Current Package

`0.1.6` includes:

- CP8000 Arduino core and board definitions for CP81-Mini.
- Board-scoped example categories:
  `01.GPIO`, `02.I2C_SPI`, `03.BLE`, `04.Serial`, `05.24GRadio`,
  `06.Watchdog`, and `07.OTA`.
- CP8xxx UART uploader integration for Windows, macOS, and Linux.
- First-run `pyserial` auto-install for uploader commands that need serial
  access.
- Vendor CP8000 runtime libraries and linker assets required by the examples.
- Boards Manager managed `cp8000-xuantie-elf-newlib@0.1.0-alpha.9` toolchain
  packages.
- Windows Boards Manager install fix: the release archive excludes local
  symlink-based toolchain wrappers and uses the managed toolchain package.

## Notes

This package is an early public release for hardware bring-up and Arduino
ecosystem validation. BLE, OTA, and production flashing workflows may still
change.
