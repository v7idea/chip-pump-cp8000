#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
VERSION="${1:-0.1.6}"
OUT_DIR="$ROOT/package/dist"
STAGE="$ROOT/package/stage"
ARCHIVE="$OUT_DIR/chippump-cp8000-$VERSION.tar.gz"

"$ROOT/scripts/sync_uploader_tool.sh" >/dev/null

rm -rf "$STAGE"
mkdir -p "$STAGE/chippump-cp8000-$VERSION" "$OUT_DIR"
cp -R "$ROOT/arduino/hardware/chippump/cp8000/." "$STAGE/chippump-cp8000-$VERSION/"

# The legacy local wrapper toolchain directory may contain symlinks. Arduino IDE
# on Windows cannot extract platform archives that contain them, and release
# builds use Boards Manager toolsDependencies instead.
rm -rf "$STAGE/chippump-cp8000-$VERSION/tools/riscv64-unknown-elf"

if find "$STAGE/chippump-cp8000-$VERSION" -type l -print -quit | grep -q .; then
  echo "error: platform package contains symlinks; Windows Boards Manager cannot install it." >&2
  find "$STAGE/chippump-cp8000-$VERSION" -type l -print >&2
  exit 1
fi

COPYFILE_DISABLE=1 tar -C "$STAGE" -czf "$ARCHIVE" "chippump-cp8000-$VERSION"
echo "$ARCHIVE"
