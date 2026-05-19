#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

docker compose -f "$ROOT/docker-dev/compose.yaml" run --rm \
  -e CP8000_FAKE_TOOLCHAIN=1 \
  arduino-cli \
  arduino-cli compile \
  --config-file /workspace/arduino-cli.yaml \
  --fqbn chippump:cp8000:cp8001_sop16 \
  /workspace/examples/Blink
