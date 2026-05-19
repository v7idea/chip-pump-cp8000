# TODO

## Public Repository

- [x] Remove private DevOps submodule dependency from the public repository.
- [x] Sync first public-safe SDK file set from `Arduino-CP8000-Develop`.
- [x] Document current vendor-file exclusions.
- [ ] Verify a clean public clone without private credentials.
- [ ] Confirm vendor SDK, static library, flash algorithm, and toolchain
      redistribution terms.

## Release Packaging

- [ ] Add GitHub Actions workflow to run SDK recipe smoke checks.
- [ ] Add GitHub Actions workflow to generate package archive and
      `package_chip-pump_cp8000_index.json`.
- [ ] Upload package archive and package index as GitHub release assets.
- [ ] Confirm package index URLs point to public assets.

## Boards Manager Validation

- [ ] Install from a clean Arduino IDE using the GitHub release package index
      URL.
- [ ] Compile Blink from the installed package.
- [ ] Upload Blink from the installed package.
- [ ] Compile and upload Serial, Wire/OLED, PWM, and BLE examples from the
      installed package.
