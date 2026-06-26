#!/usr/bin/env bash
set -euo pipefail

arduino-cli core list --config-file /workspace/arduino-cli.yaml
arduino-cli board listall --config-file /workspace/arduino-cli.yaml | grep 'CP81-Mini'

ARCHIVE="$(scripts/package_platform.sh 0.1.3)"
python3 scripts/generate_package_index.py \
  --version 0.1.3 \
  --archive "$ARCHIVE" \
  --url https://github.com/v7idea/chip-pump-cp8000/releases/download/0.1.3/chippump-cp8000-0.1.3.tar.gz

python3 -m json.tool package/package_chip-pump_cp8000_index.json >/dev/null
PYTHONPATH=tools/cp8000-uploader python3 -m cp8000_uploader --version
arduino/hardware/chippump/cp8000/tools/cp8000-uploader/cp8000-uploader --version
arduino/hardware/chippump/cp8000/tools/cp8000-uploader/cp8000-uploader upload --dry-run --port TEST --target flash --file examples/Blink/Blink.ino >/dev/null
