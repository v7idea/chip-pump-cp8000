# MVP

The MVP for this wrapper repository is a reproducible release entry point for
the CP8000 Arduino SDK.

## Required for Internal MVP

- `Arduino-CP8000-Develop` is tracked as a git submodule.
- The submodule points to a committed and pushed SDK revision in Azure DevOps.
- A developer with DevOps access can clone this repository with submodules.
- The wrapper README explains the private submodule limitation.
- The SDK package and index generation can be run from the submodule.

## Required for Public Arduino Boards Manager MVP

- Package archives are downloadable without private credentials.
- `package_chip-pump_cp8000_index.json` is downloadable without private
  credentials.
- The package index URLs point to public release assets.
- Arduino IDE can install `CHIP-PUMP CP8000` from the package index URL.
- Arduino CLI can compile and upload the bundled examples after installation.

## Not Yet MVP Complete

This wrapper is not public-release complete while the only SDK source remote is a
private DevOps repository. That is acceptable for internal development, but
public Boards Manager testing must use public release artifacts or a public SDK
mirror.
