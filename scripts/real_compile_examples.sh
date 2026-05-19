#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
FQBN="${FQBN:-chippump:cp8000:cp8001_sop16}"
LOG_DIR="${LOG_DIR:-$ROOT/build/real-compile-logs}"
TOOLCHAIN_HOST_PATH="${CP8000_TOOLCHAIN_HOST_PATH:-}"

examples=(
  Blink
  CoreHelpers
  SerialEcho
  SerialAdvanced
  AnalogReadSerial
  Fade
  I2CScanner
  OLED128x64I2C
  SPITransfer
  WatchdogReset
  FlashUID
  SleepTimed
  BLEBeacon
  BLEAdvertisingRaw
  BLEDeviceName
  BLEManufacturerData
  BLESerialBridge
  BLEConnectionStatus
  BLEUartEcho
  RF24GSend
)

mkdir -p "$LOG_DIR"

compose_args=(
  compose
  -f "$ROOT/docker-dev/compose.yaml"
  run
  --rm
)

if [[ -n "$TOOLCHAIN_HOST_PATH" ]]; then
  compose_args+=(
    -v "$TOOLCHAIN_HOST_PATH:/opt/cp8000-toolchain:ro"
    -e CP8000_TOOLCHAIN_PATH=/opt/cp8000-toolchain
  )
fi

compose_args+=(arduino-cli)

echo "Checking real CP8000 toolchain..."
if ! docker "${compose_args[@]}" scripts/check_toolchain.sh; then
  cat <<'MSG'

Real toolchain is not reachable.

Set one of:
  CP8000_TOOLCHAIN_HOST_PATH=/host/path/to/XTGccElfNewlib/V3.2.0/R
  CP8000_TOOLCHAIN_PATH=/opt/cp8000-toolchain

or link a local toolchain with:
  scripts/link_toolchain.sh /path/to/XTGccElfNewlib/V3.2.0/R
MSG
  exit 1
fi

for sketch in "${examples[@]}"; do
  log="$LOG_DIR/$sketch.log"
  echo "Compiling $sketch with $FQBN"
  docker "${compose_args[@]}" \
    arduino-cli compile \
    --config-file /workspace/arduino-cli.yaml \
    --fqbn "$FQBN" \
    "/workspace/examples/$sketch" >"$log" 2>&1
  tail -n 4 "$log"
done

echo "Logs written to $LOG_DIR"
