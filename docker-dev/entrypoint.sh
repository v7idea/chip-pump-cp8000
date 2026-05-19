#!/usr/bin/env bash
set -euo pipefail

mkdir -p /workspace/.arduino15 /workspace/arduino

if [[ ! -f /workspace/arduino-cli.yaml ]]; then
  cat > /workspace/arduino-cli.yaml <<'YAML'
directories:
  data: /workspace/.arduino15
  downloads: /workspace/.arduino15/staging
  user: /workspace/arduino
board_manager:
  additional_urls: []
YAML
fi

exec "$@"
