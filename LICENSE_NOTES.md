# License Notes

This project currently contains imported vendor SDK files and vendor binary libraries. Public release requires a license review before distributing the Arduino package archive.

## Items Requiring Confirmation

- CP800X vendor SDK source redistribution.
- Vendor static libraries:
  - `libstartlib.a`
  - `libblebase.a`
  - `libblestack.a`
  - `lib2g4_base.a`
  - `librf2g4.a`
- C-Sky/CDK E902M toolchain redistribution.
- CP8xxx Debug Tool redistribution or replacement.
- Arduino package index hosting rights for bundled artifacts.

## Current Release Position

The repository is suitable for internal SDK development. It is not yet cleared for public Boards Manager distribution.

## Preferred Public Release Model

If licenses allow redistribution:

- Publish a versioned CP8000 Arduino platform archive.
- Publish a package index with checksums and sizes.
- Publish or reference redistributable tool archives.

If licenses do not allow redistribution:

- Keep vendor SDK and toolchain installation as documented prerequisites.
- Package only open project files.
- Add scripts that import local vendor files into the Arduino platform tree.

## Review Record

```text
Date:
Reviewer:
Vendor contact:
SDK redistribution:
Toolchain redistribution:
Uploader redistribution:
Notes:
```
