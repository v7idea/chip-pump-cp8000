#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BIN_DIR="$ROOT/arduino/hardware/chippump/cp8000/tools/riscv64-unknown-elf/bin"

missing=0

for tool in gcc g++ ar objcopy objdump size; do
  name="riscv64-unknown-elf-$tool"
  path="$BIN_DIR/$name"
  if [[ ! -x "$path" ]]; then
    echo "missing wrapper or binary: $path"
    missing=1
    continue
  fi

  if "$path" --version >/tmp/"$name.version" 2>/tmp/"$name.err"; then
    head -n 1 /tmp/"$name.version"
  else
    echo "$name exists, but real toolchain is not reachable"
    sed -n '1,12p' /tmp/"$name.err"
    missing=1
  fi
done

exit "$missing"
