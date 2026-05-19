#!/usr/bin/env bash
set -euo pipefail

if [[ $# -ne 1 ]]; then
  echo "usage: $0 /path/to/XTGccElfNewlib/V3.2.0/R" >&2
  exit 2
fi

SRC="$(cd "$1" && pwd)"
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BIN_DIR="$ROOT/arduino/hardware/chippump/cp8000/tools/riscv64-unknown-elf/bin"

mkdir -p "$BIN_DIR"

for tool in gcc g++ ar objcopy objdump size readelf nm ranlib strip; do
  name="riscv64-unknown-elf-$tool"
  if [[ -x "$SRC/bin/$name" ]]; then
    ln -sf "$SRC/bin/$name" "$BIN_DIR/$name"
  elif [[ -x "$SRC/$name" ]]; then
    ln -sf "$SRC/$name" "$BIN_DIR/$name"
  else
    echo "warning: $name not found under $SRC" >&2
  fi
done

echo "Linked toolchain binaries into $BIN_DIR"
