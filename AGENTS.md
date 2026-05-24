# Agent Notes

## Boards Manager Release Rule

Public Arduino users must always use the stable Boards Manager URL:

```text
https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json
```

For every package release, issue fix, upload recipe change, platform archive
change, toolchain metadata change, or public install instruction update:

1. Generate the versioned `package/package_chip-pump_cp8000_index.json`.
2. Publish the normal versioned release assets.
3. Update the stable `boards-manager` release asset with `--clobber`.
4. Verify the stable URL reports the intended newest platform version.

Required command:

```bash
gh release upload boards-manager package/package_chip-pump_cp8000_index.json \
  --repo v7idea/chip-pump-cp8000 --clobber
```

Do not mark a Boards Manager related issue as fixed until the stable URL has
been updated and verified.
