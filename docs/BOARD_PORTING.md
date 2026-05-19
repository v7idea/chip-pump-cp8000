# Board Porting Guide

Add one board at a time and keep every pin map explicit.

## Files To Touch

- `arduino/hardware/chippump/cp8000/boards.txt`
- `arduino/hardware/chippump/cp8000/variants/<board>/pins_arduino.h`
- `arduino/hardware/chippump/cp8000/variants/<board>/variant.cpp`
- `examples/Blink/Blink.ino` only if the default LED assumption changes.

## Board Definition Checklist

- Board menu name.
- MCU variant.
- Flash layout and linker script.
- Upload speed.
- Bootloader protocol name.
- Variant include path.
- Default LED pin.
- Default `Serial` UART.
- I2C SDA/SCL pins.
- SPI MOSI/MISO/SCK/SS pins.
- ADC-capable pins.
- PWM-capable pins.

## Pin Map Policy

- Use Arduino digital pin numbers as stable board-level API.
- Keep physical package pins documented in comments.
- Do not expose unavailable package pins.
- Prefer conservative defaults until the schematic is confirmed.

## Validation

For every new board:

```bash
FQBN=chippump:cp8000:<board_id> scripts/recipe_smoke_compile_examples.sh
```

Then repeat with the real toolchain:

```bash
FQBN=chippump:cp8000:<board_id> scripts/real_compile_examples.sh
```

Finally run the hardware bring-up checklist in `docs/HARDWARE_BRINGUP.md`.
