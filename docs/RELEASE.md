# Release Plan

This project is not ready for public Boards Manager release until the toolchain and uploader questions are resolved.

## Versioning

Use semantic versions for Arduino package releases:

```text
MAJOR.MINOR.PATCH
```

Suggested interpretation:

- `MAJOR`: breaking board/core/library API changes
- `MINOR`: new board support, new libraries, or substantial peripheral support
- `PATCH`: bug fixes, examples, packaging fixes

Development builds may use:

```text
0.1.0-dev
```

## Release Artifacts

A release should publish:

- `chippump-cp8000-{version}.tar.gz`
- `package_chip-pump_cp8000_index.json`
- changelog
- checksum record

Generate current local artifacts:

```bash
scripts/package_platform.sh 0.1.0-dev
python3 scripts/generate_package_index.py \
  --version 0.1.0-dev \
  --archive package/dist/chippump-cp8000-0.1.0-dev.tar.gz \
  --url https://example.invalid/chippump-cp8000-0.1.0-dev.tar.gz \
  --website-url https://example.invalid/chippump/cp8000 \
  --email support@example.invalid \
  --help-url https://example.invalid/chippump/cp8000/help
```

## GitHub Actions Release Packaging

`.github/workflows/release-package.yml` provides a manual release packaging
workflow. Trigger it with:

- `version`: Arduino platform version, for example `0.1.0`.
- `archive_url`: the final public download URL for
  `chippump-cp8000-{version}.tar.gz`.
- `website_url`: the project website URL used in Boards Manager metadata.
- `email`: the support email used in Boards Manager metadata.
- `help_url`: the online help URL used in Boards Manager metadata.
- `release_audit`: keep enabled for public releases.

The workflow creates:

- `package/dist/chippump-cp8000-{version}.tar.gz`
- `package/package_chip-pump_cp8000_index.json`

and uploads both as GitHub Actions artifacts.

## Release Blockers

- Confirm vendor SDK redistribution license.
- Confirm C-Sky/CDK E902M toolchain redistribution license.
- Produce or obtain a real cross-platform `cp8000-uploader`.
- Verify real `arduino-cli compile` generates `.elf`, `.hex`, `.bin`.
- Verify upload on physical CP8001/CP800X hardware.
- Replace `example.invalid` URLs with production URLs.

## Pre-Release Checklist

- [x] `scripts/check_toolchain.sh` passes with real toolchain.
- [x] `scripts/real_compile_examples.sh` passes for every example without `CP8000_FAKE_TOOLCHAIN`.
- [ ] `scripts/audit_placeholders.sh --release` passes.
- [ ] Blink runs on hardware.
- [ ] Serial works on hardware.
- [ ] GPIO, ADC, PWM, I2C, SPI smoke-tested on hardware.
- [ ] BLE Beacon visible from phone/app scanner.
- [ ] RF24G TX/RX tested with two devices.
- [ ] Package installs from Boards Manager URL.
- [ ] CI generates package index from release artifact.
