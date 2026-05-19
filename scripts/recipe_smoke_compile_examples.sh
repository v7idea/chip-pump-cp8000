#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
FQBN="${FQBN:-chippump:cp8000:cp8001_sop16}"

examples=(
  Blink
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
  BLEConnectionStatus
  BLEUartEcho
  RF24GSend
)

for sketch in "${examples[@]}"; do
  echo "== $sketch =="
  docker compose -f "$ROOT/docker-dev/compose.yaml" run --rm \
    -e CP8000_FAKE_TOOLCHAIN=1 \
    arduino-cli \
    arduino-cli compile \
    --config-file /workspace/arduino-cli.yaml \
    --fqbn "$FQBN" \
    "/workspace/examples/$sketch" >/tmp/cp8000-"$sketch".log
  tail -n 2 /tmp/cp8000-"$sketch".log
done
