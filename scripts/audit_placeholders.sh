#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
MODE="${1:-dev}"
status=0

echo "Scanning release placeholders..."
if rg -n \
  --glob '!package/stage/**' \
  --glob '!build/**' \
  --glob '!.arduino15/**' \
  --glob '!scripts/audit_placeholders.sh' \
  'example\.invalid|TODO_RELEASE|PLACEHOLDER_URL|REPLACE_BEFORE_RELEASE' "$ROOT"; then
  echo "Release placeholders found."
  [[ "$MODE" == "--release" ]] && status=1
else
  echo "No release placeholders found."
fi

echo
echo "Scanning known blocking terms..."
if rg -n \
  --glob '!package/stage/**' \
  --glob '!build/**' \
  --glob '!.arduino15/**' \
  --glob '!scripts/audit_placeholders.sh' \
  --glob '!arduino/hardware/chippump/cp8000/system/sdk/**' \
  'not implemented|ProtocolNotImplementedError|redistribution license|bootloader protocol|real toolchain is not reachable' "$ROOT"; then
  echo "Known blockers still exist."
else
  echo "No known blocker terms found."
fi

if [[ "$MODE" == "--release" ]]; then
  echo
  echo "Release mode: placeholders are fatal; blocker terms are informational."
fi

exit "$status"
