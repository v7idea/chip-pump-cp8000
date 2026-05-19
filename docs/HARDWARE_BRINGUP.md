# Hardware Bring-Up Plan

This checklist turns the Arduino package from "builds in CI" into "runs on CP8000 hardware".

## Required Equipment

- CP8001 or CP800X SOP16 reference board.
- USB-UART adapter with selectable 3.3 V logic.
- Power supply with current limit.
- Logic analyzer for UART bootloader capture.
- Oscilloscope for clock, reset, PWM, and low-power checks.
- BLE scanner app or BLE protocol analyzer.
- Second CP8000 board for 2.4G RF TX/RX testing.

## Board Information To Confirm

- Exact chip marking and package.
- Power rails and reset circuit.
- Boot mode strap pins.
- UART bootloader pins and reset timing.
- Arduino default `Serial` UART.
- LED pin for `Blink`.
- ADC-capable pins and valid voltage range.
- I2C and SPI pin mapping.
- RF matching network and antenna connection.

## Phase 1: Electrical Sanity

- Confirm idle current before flashing.
- Confirm reset pin behavior.
- Confirm main clock starts.
- Confirm UART pins idle at expected logic level.
- Confirm there is no 5 V signal on CP8000 GPIO.

## Phase 2: Build Artifact Sanity

Run with the real toolchain:

```bash
CP8000_TOOLCHAIN_HOST_PATH=/path/to/XTGccElfNewlib/V3.2.0/R \
scripts/real_compile_examples.sh
```

Check generated artifacts:

- `.elf` links against the expected linker script.
- `.bin` starts at the expected flash application base.
- `.map` contains vendor startup and Arduino `main`.
- Binary size leaves enough flash and RAM margin.

## Phase 3: First Upload

Until the UART protocol is implemented, use the vendor CP8xxx Debug Tool or protocol capture workflow.

Record:

- Tool version.
- COM port and baud rate.
- Boot mode sequence.
- Erase command behavior.
- Write block size.
- Verify or checksum command.
- Reset/run command.

## Phase 4: Arduino MVP

- `Blink`: verify LED pin and timing.
- `SerialEcho`: verify baud rate and RX/TX mapping.
- `AnalogReadSerial`: verify ADC range.
- `Fade`: verify PWM channel mapping.
- `WatchdogReset`: verify reset behavior.
- `SleepTimed`: measure current before and after sleep.

## Phase 5: Radio

- `BLEBeacon`: verify advertisement is visible from a phone.
- `RF24GSend`: verify TX/RX with two boards.
- Document channel, payload length, and observed range.

## Bring-Up Log Template

```text
Date:
Board:
Chip marking:
SDK package version:
Toolchain version:
Uploader/tool version:
Power:
Boot mode:
Sketch:
Result:
Notes:
```
