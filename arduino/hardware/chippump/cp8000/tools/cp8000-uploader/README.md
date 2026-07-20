# cp8000-uploader

Cross-platform command-line uploader for the CP8000 UART bootloader.

The CLI is integrated with Arduino `platform.txt`. The CP8xxx binary protocol
can connect, stream blocks, send the recovered checksum packet, send the
`0x1003f000` flash finalize/state packet, and send the candidate self-start
packet. Flash erase and final on-hardware app execution proof are still open.

## Intended Usage

```bash
cp8000-uploader upload \
  --protocol cp8xxx-binary \
  --flash-write-mode cached \
  --port /dev/ttyUSB0 \
  --target flash \
  --baud 115200 \
  --address 0x10000000 \
  --file Blink.bin
```

The binary uploader keeps sending the recovered vendor connect prelude followed
by the shorter empty binary sync for `--connect-timeout` seconds (`20` by
default). Start upload first, then reset or power-cycle the target so the ROM
bootloader can catch the sequence. This `prelude-sync` default matches the
hardware-validated vendor GUI flow recovered in commit `db48270`.

During Arduino IDE uploads the uploader prints a reset prompt, confirms the
bootloader ACK when the CP8000 is really in bootloader mode, then prints flash
progress dots and 10% progress markers while chunks are programmed.

For A/B probing, `--entry-sync-mode` can be set to `prelude-only` or
`sync-only`, but the Arduino platform default stays on `prelude-sync`.

Boards with USB-UART DTR/RTS wired to reset or boot-entry circuitry can opt
into a pre-sync control-line pulse:

```bash
cp8000-uploader binary-probe \
  --port /dev/ttyUSB0 \
  --baud 115200 \
  --boot-reset-method pulse-dtr
```

Supported methods are `none`, `pulse-dtr`, `pulse-rts`, `dtr-rts`, and
`rts-dtr`. The default is `none` because CP8000 development boards may expose
only TX/RX/GND, and the wrong control-line pulse should not disturb a working
manual boot flow.

`--flash-write-mode cached` loads the large RAM flash algorithm once before the
programming loop and is the Arduino platform default. Use
`--flash-write-mode safe` to return to the older conservative behavior that
reloads the flash algorithm for every 1024-byte chunk.

After upload, the default `--reset-method self-start` sends the recovered
`0x000004ee` command with `--run-address`. The default run address is the
vendor GUI's initialized self-start address, `0x20002000`; pass
`--run-address 0x10000000` to test a direct flash-app jump. Hardware currently
ACKs this packet but has not yet proven that it exits the ROM bootloader and
starts a flash application. Use `--reset-method none` when you want to upload,
close the port, and manually power-cycle the target for boot validation.

## Protocol Capture Helper

The vendor documents confirm a Windows GUI workflow but do not expose the UART
wire protocol. Use `capture` to collect raw serial traffic while reproducing a
GUI flashing session:

```bash
cp8000-uploader capture \
  --port /dev/ttyUSB0 \
  --baud 115200 \
  --output captures/cp8000-flash-default.bin
```

Omit `--output` to print timestamped hex to stdout. Keep a raw binary capture
for protocol analysis.

## Experimental PHY62XX Text Protocol

`SDK/37129040379277025281615529461919ksaxe4HpZw.pdf` documents a PHY62XX
UART-to-FLASH text-command protocol. CP800X compatibility is not confirmed, but
the uploader can try it explicitly:

```bash
cp8000-uploader upload \
  --protocol phy62xx-text \
  --port /dev/ttyUSB0 \
  --target flash \
  --baud default \
  --address 0x10000000 \
  --file Blink.bin
```

With `--baud default`, the tool sends the documented DWC sequence `UXTDWU` at
`9600` baud, then reopens the port at `115200` and waits for `cmd>>:`.

## Required Protocol Work

1. Open serial port.
2. Send or wait for bootloader handshake while the chip resets. Implemented for
   CP8xxx binary sync with a retry window.
3. Select RAM, OTP, or FLASH target. Implemented for the observed FLASH write
   path.
4. Erase when needed. Still unidentified in the CP8xxx binary protocol.
5. Stream firmware chunks. Implemented with 1024-byte data blocks and 32-bit
   word-count block headers.
6. Verify checksum. Implemented experimentally with the recovered flash
   checksum packet followed by the `0x1003f000` finalize/state packet.
7. Reset or jump to application. Implemented experimentally with the recovered
   self-start packet; hardware ACK is confirmed, but app execution is not.

The vendor documents say the CP8xxx enters bootloader programming mode when it receives a special UART command immediately after power-on/reset.
