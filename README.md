# CHIP-PUMP CP8000 Arduino SDK

Arduino Boards Manager package for CHIP-PUMP CP8000/CP800X boards.

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
`0.1.1-alpha.4`, uploader commands that need a serial port check for
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
7. Select a board such as **CHIP-PUMP CP8001 SOP16**.
8. Select the correct serial port and upload an example.

If Arduino IDE does not show the newest CP8000 version, close Arduino IDE and
delete these cached files under:

```text
C:\Users\<USER>\AppData\Local\Arduino15
```

```text
package_chip-pump_cp8000_index.json
package_chip-pump_cp8000_index.json.sig
staging\packages\chippump-cp8000-*.tar.gz
```

Then reopen Arduino IDE and check the Boards Manager version dropdown.

## Arduino CLI Install

```bash
arduino-cli core update-index \
  --additional-urls https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json

arduino-cli core install chippump:cp8000@0.1.1-alpha.4 \
  --additional-urls https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json
```

Compile Blink:

```bash
arduino-cli compile \
  --fqbn chippump:cp8000:cp8001_sop16 \
  arduino/hardware/chippump/cp8000/libraries/01.GPIO/examples/Blink
```

## Current Package

`0.1.1-alpha.4` includes:

- CP8000 Arduino core and board definitions for CP8001 SOP16 and CP8003 SOP16.
- Board-scoped example categories:
  `01.GPIO`, `02.I2C_SPI`, `03.BLE`, `04.Serial`, `05.24GRadio`,
  `06.Watchdog`, and `07.OTA`.
- CP8xxx UART uploader integration for Windows, macOS, and Linux.
- First-run `pyserial` auto-install for uploader commands that need serial
  access.
- Vendor CP8000 runtime libraries and linker assets required by the examples.
- Boards Manager managed `cp8000-xuantie-elf-newlib@0.1.0-alpha.9` toolchain
  packages.

## Notes

This package is an alpha release for hardware bring-up and Arduino ecosystem
validation. BLE, OTA, and production flashing workflows may still change.
