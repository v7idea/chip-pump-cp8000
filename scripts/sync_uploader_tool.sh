#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SRC="$ROOT/tools/cp8000-uploader"
DEST="$ROOT/arduino/hardware/chippump/cp8000/tools/cp8000-uploader"

rm -rf "$DEST"
mkdir -p "$DEST"
cp -R "$SRC/." "$DEST/"

cat > "$DEST/cp8000-uploader" <<'SH'
#!/usr/bin/env bash
set -euo pipefail
DIR="$(cd "$(dirname "$0")" && pwd)"
PYTHON="${PYTHON:-python3}"
PYTHONPATH="$DIR${PYTHONPATH:+:$PYTHONPATH}" exec "$PYTHON" -m cp8000_uploader "$@"
SH

cat > "$DEST/cp8000-uploader.cmd" <<'BAT'
@echo off
set DIR=%~dp0
if "%PYTHON%"=="" set PYTHON=python
set PYTHONPATH=%DIR%;%PYTHONPATH%
"%PYTHON%" -m cp8000_uploader %*
BAT

chmod +x "$DEST/cp8000-uploader"
echo "Synced uploader tool to $DEST"
