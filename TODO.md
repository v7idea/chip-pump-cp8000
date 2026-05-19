# TODO

## Repository Wrapper

- [x] Add `Arduino-CP8000-Develop` as a git submodule.
- [x] Point the submodule at the Azure DevOps SDK development repository.
- [x] Document that the current submodule is private and requires DevOps access.
- [ ] Verify a clean clone with `git clone --recurse-submodules`.
- [ ] Decide whether the public release path uses GitHub release artifacts or a
      public SDK mirror.

## Release Packaging

- [ ] Add GitHub Actions workflow to initialize the submodule.
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
