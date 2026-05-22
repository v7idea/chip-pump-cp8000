#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
VERSION="${1:-0.1.0-alpha.8}"
OUT_DIR="$ROOT/package/dist"
STAGE="$ROOT/package/stage"
ARCHIVE="$OUT_DIR/chippump-cp8000-$VERSION.tar.gz"

"$ROOT/scripts/sync_uploader_tool.sh" >/dev/null

rm -rf "$STAGE"
mkdir -p "$STAGE/chippump-cp8000-$VERSION" "$OUT_DIR"
cp -R "$ROOT/arduino/hardware/chippump/cp8000/." "$STAGE/chippump-cp8000-$VERSION/"

COPYFILE_DISABLE=1 tar -C "$STAGE" -czf "$ARCHIVE" "chippump-cp8000-$VERSION"
echo "$ARCHIVE"
