# Uploader Optimization MVP

This document defines the minimum viable optimization plan for the CP8000
Arduino uploader. The goal is to make the current working macOS/Arduino CLI
flash path feel close to the Windows vendor GUI while keeping the protocol work
incremental and hardware-safe.

## Current Problem

The current uploader is correct enough to program Blink, but it is slow because
each 1024-byte firmware chunk repeats the whole RAM helper setup:

1. Load the 2272-byte vendor flash algorithm to `0x20000000`.
2. Load the firmware data chunk to `0x20001000`.
3. Load the control record to `0x20003700`.
4. Load the 56-byte program stub to `0x20002000`.
5. Self-start the stub.
6. Wait for the bootloader to respond again.

For an 8 KB firmware this repeats the flash algorithm 8 times, adding roughly
18 KB of unnecessary UART traffic plus repeated bootloader re-sync waits.

## MVP Goal

Reduce upload time without changing the proven flash write semantics:

- Keep the confirmed CP8xxx binary handshake.
- Keep the confirmed erase, checksum, and finalize commands.
- Keep 1024-byte firmware chunks for the first optimized version.
- Load the large flash algorithm once per upload.
- Avoid reloading static RAM code between chunks unless hardware proves it is
  overwritten.

Success means Blink upload time is clearly shorter and still boots/flashes at
least as reliably as the current release path.

## Proposed MVP Flow

### Baseline Flow

Keep the existing implementation as a fallback mode:

```text
connect
load flash algorithm
load erase stub
self-start erase stub
sync
for each chunk:
  load flash algorithm
  load data buffer
  load control record
  load program stub
  self-start program stub
  sync
write checksum
finalize flash
self-start/reset
```

### Optimized Flow V1

Load invariant RAM assets once, then only update data and control for each
chunk:

```text
connect
load flash algorithm
load erase stub
self-start erase stub
sync
load flash algorithm
load program stub
for each chunk:
  load data buffer
  load control record
  self-start program stub
  sync
write checksum
finalize flash
self-start/reset
```

This removes repeated `flash-algorithm` transfer and may remove repeated
`program-stub` transfer. If the stub or ROM clobbers `0x20002000`, keep
`program-stub` reload per chunk but still keep the flash algorithm loaded once.

### Optimized Flow V2

If V1 is stable, enlarge the firmware data chunk:

- Try 2048 bytes.
- Try 4096 bytes.
- Keep 1024 bytes as the default if larger chunks fail.

The CP8xxx address+data packet path currently limits `_send_ram_data()` to
1024-byte packets, but the program helper could still write larger flash chunks
if we stage a bigger buffer through multiple RAM packets before one self-start.

## Implementation Plan

1. Add an uploader option:

   ```text
   --flash-write-mode safe|cached
   ```

   `safe` keeps the current behavior. `cached` enables Optimized Flow V1.
   During development, default to `safe`; after hardware validation, change the
   Arduino `platform.txt` default to `cached`.

2. Refactor `_write_flash_with_ram_helper()` into explicit stages:

   - `_prepare_flash_programming_cached()`
   - `_program_flash_chunk(block_index, flash_address, chunk, reload_stub)`
   - `_sync_after_program_chunk()`

3. Track cached RAM state in the protocol object:

   ```text
   flash_algorithm_loaded: bool
   program_stub_loaded: bool
   ```

4. Add verbose timing logs:

   ```text
   cp8xxx-binary: timing load-flash-algorithm 2.43s
   cp8xxx-binary: timing program-chunk[3] 1.18s
   cp8xxx-binary: timing total-upload 18.72s
   ```

5. Keep every hardware-risky change behind the new option until we have at
   least three successful uploads in a row.

## Validation Matrix

For every optimization step, run:

- Compile Blink through Arduino CLI.
- Upload Blink three times in a row.
- Confirm uploader checksum/finalize ACK.
- Power-cycle the board and observe LED behavior.
- Save uploader timing logs.

Recommended test cases:

| Case | Mode | Expected Result |
| --- | --- | --- |
| Baseline | `safe` | Same behavior as current working uploader |
| V1-A | `cached`, reload stub per chunk | Faster than baseline, same reliability |
| V1-B | `cached`, keep stub resident | Faster than V1-A, only keep if stable |
| V2-A | `cached`, 2048-byte flash chunk | Faster or rejected cleanly |
| V2-B | `cached`, 4096-byte flash chunk | Fastest candidate, only keep if stable |

## Risk Controls

- Do not remove the current safe path.
- Do not change erase/finalize until write speed is improved and stable.
- If cached mode times out after a chunk, fall back to reloading the flash
  algorithm once and retry the same chunk.
- If fallback succeeds, print a warning and continue; if it fails, stop with a
  clear error.
- Preserve the exported `.bin` checksum so Windows GUI and Arduino CLI can be
  compared with the same firmware image.

## Expected Impact

The current 8 KB Blink upload reloads the 2272-byte flash algorithm eight times.
V1 should reduce that to two loads: one for erase and one for program. That
removes six algorithm transfers and six related waits.

The practical speedup should be visible immediately even before larger chunks:

- Less UART traffic.
- Fewer long sync windows.
- Cleaner verbose output.

If V2 larger chunks work, upload time should approach the vendor GUI more
closely because the number of RAM self-start cycles drops as well.

## Done Criteria

- `--flash-write-mode safe` still passes the current Blink upload path.
- `--flash-write-mode cached` uploads Blink successfully three times in a row.
- Cached mode prints per-stage timing.
- Arduino CLI can opt into cached mode through `platform.txt`.
- `docs/UPLOADER_PROTOCOL.md` records the validated optimized flow and any
  rejected larger chunk sizes.

## Implementation Status

Implemented in the development and packaged uploader:

- `--flash-write-mode safe|cached`
- `--boot-reset-method none|pulse-dtr|pulse-rts|dtr-rts|rts-dtr`
- `cached` as the Arduino `platform.txt` upload default
- per-stage timing logs in verbose mode
- cached flash algorithm load before programming chunks
- fallback retry that reloads the flash algorithm if a cached chunk times out
- immediate return after a complete 12-byte CP8xxx ACK is received

The first cached implementation still reloads the small 56-byte program stub
for every chunk. That keeps the hardware risk low while removing the repeated
2272-byte flash algorithm transfer. Keeping the stub resident is the next
optimization after cached mode is hardware-validated.

First hardware result with the active-high D0/D1 Blink image:

- Before ACK early-return optimization: `139.98s`
- After ACK early-return optimization: `10.55s`
- Firmware size: `7640 bytes`
- Checksum: `0x000a98f4`

Pre-sync control-line probe result on `/dev/cu.usbserial-A50285BI`:

- `pulse-dtr`: no bytes received
- `pulse-rts`: no bytes received
- `dtr-rts`: no bytes received
- `rts-dtr`: no bytes received
- `none`: no bytes received

This suggests the currently used USB-TTL path is TX/RX/GND-only or does not
wire DTR/RTS to CP8000 reset/boot-entry pins. Keep manual reset/power-cycle as
the active path until a board wiring with boot control lines is identified.
