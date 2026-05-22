#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
VERSION="${1:-0.1.0-alpha.7}"
TAG="${2:-$VERSION}"
OUT_DIR="$ROOT/package/dist"
STAGE_DIR="$ROOT/package/tool-stage"
META="$ROOT/package/tool_releases.json"
BASE_URL="https://github.com/v7idea/chip-pump-cp8000/releases/download/$TAG"
TOOL_NAME="cp8000-xuantie-elf-newlib"

LINUX_X86_64_TOOLCHAIN="${LINUX_X86_64_TOOLCHAIN:-$ROOT/../SDK/Xuantie-900-gcc-elf-newlib-x86_64-V3.4.0}"
LINUX_I386_TOOLCHAIN="${LINUX_I386_TOOLCHAIN:-$ROOT/../SDK/Xuantie-900-gcc-elf-newlib-i386-V3.4.0}"
MACOS_ARM64_TOOLCHAIN="${MACOS_ARM64_TOOLCHAIN:-/tmp/cp8000-xuantie-build/install}"
WINDOWS_X86_64_TOOLCHAIN="${WINDOWS_X86_64_TOOLCHAIN:-}"

mkdir -p "$OUT_DIR"

systems_json=()

package_one() {
  local host="$1"
  local source_dir="$2"
  local archive="$OUT_DIR/$TOOL_NAME-$VERSION-$host.tar.gz"
  local root_dir="$TOOL_NAME-$VERSION-$host"

  if [ ! -x "$source_dir/bin/riscv64-unknown-elf-gcc" ] && [ ! -x "$source_dir/bin/riscv64-unknown-elf-gcc.exe" ]; then
    printf 'skip %s: missing compiler at %s/bin/riscv64-unknown-elf-gcc\n' "$host" "$source_dir" >&2
    return 0
  fi

  printf 'packaging %s from %s\n' "$host" "$source_dir" >&2
  rm -rf "$STAGE_DIR/$root_dir"
  mkdir -p "$STAGE_DIR/$root_dir"
  rsync -a --delete --exclude '.DS_Store' "$source_dir/" "$STAGE_DIR/$root_dir/"
  COPYFILE_DISABLE=1 tar -C "$STAGE_DIR" -czf "$archive" "$root_dir"

  local checksum
  checksum="$(shasum -a 256 "$archive" | awk '{print "SHA-256:" $1}')"
  local size
  size="$(wc -c < "$archive" | tr -d ' ')"
  systems_json+=("$(python3 - "$host" "$BASE_URL/$(basename "$archive")" "$(basename "$archive")" "$checksum" "$size" <<'PY'
import json
import sys

print(json.dumps({
    "host": sys.argv[1],
    "url": sys.argv[2],
    "archiveFileName": sys.argv[3],
    "checksum": sys.argv[4],
    "size": sys.argv[5],
}))
PY
)")
}

package_one "x86_64-linux-gnu" "$LINUX_X86_64_TOOLCHAIN"
package_one "i686-linux-gnu" "$LINUX_I386_TOOLCHAIN"
package_one "arm64-apple-darwin" "$MACOS_ARM64_TOOLCHAIN"
if [ -n "$WINDOWS_X86_64_TOOLCHAIN" ]; then
  package_one "x86_64-mingw32" "$WINDOWS_X86_64_TOOLCHAIN"
fi

python3 - "$META" "$TOOL_NAME" "$VERSION" "${systems_json[@]}" <<'PY'
import json
import sys
from pathlib import Path

meta = Path(sys.argv[1])
tool_name = sys.argv[2]
version = sys.argv[3]
systems = [json.loads(item) for item in sys.argv[4:]]
if not systems:
    raise SystemExit("no toolchain systems were packaged")

meta.write_text(
    json.dumps(
        [
            {
                "name": tool_name,
                "version": version,
                "systems": systems,
            }
        ],
        indent=2,
    )
    + "\n",
    encoding="utf-8",
)
print(meta)
PY
