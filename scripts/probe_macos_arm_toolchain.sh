#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

candidate_roots=()
candidate_bins=()

if [[ -n "${CP8000_TOOLCHAIN_PATH:-}" ]]; then
  candidate_roots+=("$CP8000_TOOLCHAIN_PATH")
fi

if [[ -n "${CDK_TOOLCHAIN_PATH:-}" ]]; then
  candidate_roots+=("$CDK_TOOLCHAIN_PATH")
fi

candidate_roots+=(
  "$ROOT/../SDK/Xuantie-900-gcc-elf-newlib-macos-arm64-V3.4.0"
  "$ROOT/../SDK/Xuantie-900-gcc-elf-newlib-aarch64-darwin-V3.4.0"
  "$ROOT/../SDK/Xuantie-900-gcc-elf-newlib-darwin-arm64-V3.4.0"
  "/opt/homebrew/opt/riscv64-elf-gcc"
  "/opt/homebrew"
)

for root in "${candidate_roots[@]}"; do
  candidate_bins+=("$root/bin/riscv64-unknown-elf-gcc")
  candidate_bins+=("$root/riscv64-unknown-elf-gcc")
done

if command -v riscv64-unknown-elf-gcc >/dev/null 2>&1; then
  candidate_bins+=("$(command -v riscv64-unknown-elf-gcc)")
fi

if command -v riscv64-elf-gcc >/dev/null 2>&1; then
  candidate_bins+=("$(command -v riscv64-elf-gcc)")
fi

echo "Host: $(uname -s) $(uname -m)"
echo

seen=""
found_any=0
passed_any=0

for gcc in "${candidate_bins[@]}"; do
  [[ -n "$gcc" ]] || continue
  [[ -x "$gcc" ]] || continue
  real="$(python3 - "$gcc" <<'PY'
import os, sys
print(os.path.realpath(sys.argv[1]))
PY
)"
  case ":$seen:" in
    *":$real:"*) continue ;;
  esac
  seen="$seen:$real"
  found_any=1

  echo "== $gcc =="
  file "$gcc" || true
  "$gcc" --version | sed -n '1,2p'

  ok=1

  if ! "$gcc" -mcpu=e902m -x c -c /dev/null -o /tmp/cp8000-probe.o >/tmp/cp8000-probe.log 2>&1; then
    ok=0
    echo "FAIL: compiler does not accept -mcpu=e902m"
    sed -n '1,8p' /tmp/cp8000-probe.log
  else
    echo "OK: accepts -mcpu=e902m"
  fi

  if "$gcc" -print-multi-lib 2>/dev/null | grep -q 'rv32emc/ilp32e'; then
    echo "OK: rv32emc/ilp32e multilib exists"
  else
    ok=0
    echo "FAIL: rv32emc/ilp32e multilib not found"
  fi

  if "$gcc" -mcpu=e902m -dM -E -x c /dev/null 2>/dev/null | grep -q '__riscv_xtheadse'; then
    echo "OK: __riscv_xtheadse is defined for -mcpu=e902m"
  else
    ok=0
    echo "FAIL: __riscv_xtheadse is not defined for -mcpu=e902m"
  fi

  if [[ "$ok" == "1" ]]; then
    passed_any=1
    echo "RESULT: usable CP8000 macOS native candidate"
  else
    echo "RESULT: not yet safe for CP8000 Arduino builds"
  fi
  echo
done

rm -f /tmp/cp8000-probe.o /tmp/cp8000-probe.log

if [[ "$found_any" == "0" ]]; then
  cat <<'EOF'
No native candidate compiler was found.

Next options:
  1. Check whether OCC/XuanTie provides a Darwin arm64 ELF/Newlib package.
  2. Build XUANTIE-RV/xuantie-gnu-toolchain natively on macOS ARM.
  3. Try Homebrew riscv64-elf-gcc, then rerun this probe.
EOF
  exit 2
fi

if [[ "$passed_any" == "0" ]]; then
  exit 1
fi
