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


def platform_entry(
    version: str,
    archive_name: str,
    url: str,
    checksum: str,
    size: str,
    tools_dependencies: list[dict] | None = None,
) -> dict:
    return {
        "name": "CHIP-PUMP CP8000 Boards",
        "architecture": "cp8000",
        "version": version,
        "category": "Contributed",
        "url": url,
        "archiveFileName": archive_name,
        "checksum": checksum,
        "size": size,
        "boards": [
            {"name": "CP81-Mini"},
        ],
        "toolsDependencies": tools_dependencies or [],
    }


def version_key(version: str) -> tuple:
    base, separator, prerelease = version.partition("-")
    base_parts = tuple(int(part) for part in base.split("."))
    if not separator:
        return (base_parts, 1, ())

    prerelease_parts = []
    for part in prerelease.replace("-", ".").split("."):
        prerelease_parts.append((0, int(part)) if part.isdigit() else (1, part))
    return (base_parts, 0, tuple(prerelease_parts))


def main() -> int:
    parser = argparse.ArgumentParser(description="Generate Arduino Boards Manager package index.")
    parser.add_argument("--version", default="0.1.3")
    parser.add_argument("--archive", required=True, help="Path to platform archive")
    parser.add_argument("--url", required=True, help="Download URL for platform archive")
    parser.add_argument("--output", default="package/package_chip-pump_cp8000_index.json")
    parser.add_argument("--maintainer", default="CHIP-PUMP CP8000 Arduino SDK Team")
    parser.add_argument("--website-url", default="https://github.com/v7idea/chip-pump-cp8000")
    parser.add_argument("--email", default="support@v7idea.com")
    parser.add_argument("--help-url", default="https://github.com/v7idea/chip-pump-cp8000/issues")
    parser.add_argument(
        "--previous-platforms",
        default="package/platform_releases.json",
        help="JSON array of previous platform release metadata to keep in the package index",
    )
    parser.add_argument(
        "--tool-releases",
        default="package/tool_releases.json",
        help="JSON array of Arduino tool release metadata to include in the package index",
    )
    args = parser.parse_args()

    archive = Path(args.archive)
    if not archive.is_file():
        raise SystemExit(f"archive not found: {archive}")

    platforms = []
    previous_platforms = Path(args.previous_platforms)
    if previous_platforms.is_file():
        previous = json.loads(previous_platforms.read_text(encoding="utf-8"))
        for entry in previous:
            platforms.append(
                platform_entry(
                    entry["version"],
                    entry["archiveFileName"],
                    entry["url"],
                    entry["checksum"],
                    entry["size"],
                    entry.get("toolsDependencies", []),
                )
            )

    tools = []
    current_tools_dependencies = []
    tool_releases = Path(args.tool_releases)
    if tool_releases.is_file():
        tools = json.loads(tool_releases.read_text(encoding="utf-8"))
        for tool in tools:
            current_tools_dependencies.append(
                {
                    "packager": "chippump",
                    "name": tool["name"],
                    "version": tool["version"],
                }
            )

    current = platform_entry(
        args.version,
        archive.name,
        args.url,
        sha256(archive),
        str(archive.stat().st_size),
        current_tools_dependencies,
    )
    platforms = [entry for entry in platforms if entry["version"] != args.version]
    platforms.append(current)
    platforms.sort(key=lambda item: version_key(item["version"]), reverse=True)

    package = {
        "packages": [
            {
                "name": "chippump",
                "maintainer": args.maintainer,
                "websiteURL": args.website_url,
                "email": args.email,
                "help": {"online": args.help_url},
                "platforms": platforms,
                "tools": tools,
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
