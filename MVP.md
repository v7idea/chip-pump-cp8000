# MVP

The MVP for this public repository is a reproducible release entry point for the
CP8000 Arduino SDK.

## Required for Internal MVP

- This repository has no private submodule dependency.
- A developer can clone this repository without Azure DevOps access.
- Public-safe SDK files are synced from the private development repository.
- The README explains which vendor files are intentionally excluded.
- Package and index generation commands exist in this repository.

## Required for Public Arduino Boards Manager MVP

- Package archives are downloadable without private credentials.
- `package_chip-pump_cp8000_index.json` is downloadable without private
  credentials.
- The package index URLs point to public release assets.
- Arduino IDE can install `CHIP-PUMP CP8000` from the package index URL.
- Arduino CLI can compile and upload the bundled examples after installation.

## Not Yet MVP Complete

This repository is not public-release complete until required vendor SDK source,
static libraries, flash algorithm files, and toolchain distribution terms are
confirmed. Public Boards Manager testing must use release artifacts that can be
downloaded without private credentials.
