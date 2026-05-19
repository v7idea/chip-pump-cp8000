# CHIP-PUMP CP8000 Arduino Package

Public release wrapper for the CP8000/CP800X Arduino SDK.

The SDK source currently lives in the `Arduino-CP8000-Develop` git submodule.
That submodule points to the private Azure DevOps development repository:

```text
https://dev.azure.com/v7idea/Arduino-CP8000-Develop/_git/Arduino-CP8000-Develop
```

This is intentional during bring-up: day-to-day SDK development can continue in
the private DevOps repository, while this GitHub repository records the exact SDK
commit intended for packaging and release.

## Important Access Note

Because the current submodule repository is private, a public
`git clone --recurse-submodules` will only work for developers who have Azure
DevOps access.

For an Arduino Boards Manager public release, the generated package archive and
`package_chip-pump_cp8000_index.json` must be hosted at public URLs. Arduino IDE
users should not need access to the private DevOps submodule.

Before public release, choose one of these distribution paths:

- publish complete package archives as GitHub release assets from this wrapper
  repository
- mirror the SDK source to a public GitHub repository and point the submodule at
  that public mirror

## Clone for Internal Development

```bash
git clone --recurse-submodules https://github.com/v7idea/chip-pump-cp8000.git
cd chip-pump-cp8000
```

If the repository was cloned without submodules:

```bash
git submodule update --init --recursive
```

## Update SDK Pointer

After SDK changes are committed and pushed to Azure DevOps:

```bash
git submodule update --remote Arduino-CP8000-Develop
git status
git add Arduino-CP8000-Develop
git commit -m "Update CP8000 Arduino SDK submodule"
git push origin main
```

## Package Preparation

Run release packaging commands from the submodule:

```bash
cd Arduino-CP8000-Develop
make package
make index
```

The package index and archive URLs must be reviewed before public Boards Manager
testing.

## Boards Manager Goal

The final public URL should be usable in Arduino IDE:

```text
https://github.com/v7idea/chip-pump-cp8000/releases/latest/download/package_chip-pump_cp8000_index.json
```

This URL is the intended direction. It should only be published after the
release workflow uploads the package index and archive assets.
