#!/usr/bin/env python3
import argparse
import hashlib
import json
from pathlib import Path


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1024 * 1024), b""):
            digest.update(chunk)
    return "SHA-256:" + digest.hexdigest()


def main() -> int:
    parser = argparse.ArgumentParser(description="Generate Arduino Boards Manager package index.")
    parser.add_argument("--version", default="0.1.0-alpha.1")
    parser.add_argument("--archive", required=True, help="Path to platform archive")
    parser.add_argument("--url", required=True, help="Download URL for platform archive")
    parser.add_argument("--output", default="package/package_chip-pump_cp8000_index.json")
    parser.add_argument("--maintainer", default="CHIP-PUMP CP8000 Arduino SDK Team")
    parser.add_argument("--website-url", default="https://github.com/v7idea/chip-pump-cp8000")
    parser.add_argument("--email", default="support@v7idea.com")
    parser.add_argument("--help-url", default="https://github.com/v7idea/chip-pump-cp8000/issues")
    args = parser.parse_args()

    archive = Path(args.archive)
    if not archive.is_file():
        raise SystemExit(f"archive not found: {archive}")

    package = {
        "packages": [
            {
                "name": "chippump",
                "maintainer": args.maintainer,
                "websiteURL": args.website_url,
                "email": args.email,
                "help": {"online": args.help_url},
                "platforms": [
                    {
                        "name": "CHIP-PUMP CP8000 Boards",
                        "architecture": "cp8000",
                        "version": args.version,
                        "category": "Contributed",
                        "url": args.url,
                        "archiveFileName": archive.name,
                        "checksum": sha256(archive),
                        "size": str(archive.stat().st_size),
                        "boards": [
                            {"name": "CHIP-PUMP CP8001 SOP16"},
                            {"name": "CHIP-PUMP CP8003 SOP16"},
                        ],
                        "toolsDependencies": [],
                    }
                ],
                "tools": [],
            }
        ]
    }

    output = Path(args.output)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(package, indent=2) + "\n", encoding="utf-8")
    print(output)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
