# Docker Development Environment

This directory provides a reproducible Arduino CLI environment for CP8000 core development.

## Build

```bash
docker compose build
```

The CP8000 toolchain currently downloaded for this project is a Linux x86_64 binary. On Apple Silicon Macs, keep the compose platform at the default `linux/amd64` so Docker can run it through emulation.

## Shell

```bash
docker compose run --rm arduino-cli bash
```

## Smoke Tests

Inside the container:

```bash
scripts/docker_smoke_test.sh
```

Full compile requires the CP8000 RISC-V E902M toolchain under:

```text
arduino/hardware/chippump/cp8000/tools/riscv64-unknown-elf/bin/
```

The expected compiler command is:

```text
riscv64-unknown-elf-gcc
```

With the downloaded Xuantie ELF/Newlib toolchain:

```bash
CP8000_TOOLCHAIN_HOST_PATH=../SDK/Xuantie-900-gcc-elf-newlib-x86_64-V3.4.0 \
../scripts/real_compile_examples.sh
```
