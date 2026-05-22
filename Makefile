VERSION ?= 0.1.0-alpha.5
FQBN ?= chippump:cp8000:cp8001_sop16
PACKAGE_URL ?= https://github.com/v7idea/chip-pump-cp8000/releases/download/$(VERSION)/chippump-cp8000-$(VERSION).tar.gz
PACKAGE_WEBSITE_URL ?= https://github.com/v7idea/chip-pump-cp8000
PACKAGE_EMAIL ?= support@v7idea.com
PACKAGE_HELP_URL ?= https://github.com/v7idea/chip-pump-cp8000/issues

.PHONY: help docker-build smoke examples real-examples package index audit release-audit check-toolchain import-sdk

help:
	@printf '%s\n' \
		'Targets:' \
		'  docker-build     Build the Arduino CLI Docker image' \
		'  smoke            Run fake-toolchain Arduino recipe smoke compile' \
		'  examples         Run fake-toolchain compile recipe for all examples' \
		'  real-examples    Run real toolchain compile for all examples' \
		'  package          Create package/dist/chippump-cp8000-$(VERSION).tar.gz' \
		'  index            Generate package/package_chip-pump_cp8000_index.json' \
		'  audit            Check release placeholders and known blockers' \
		'  release-audit    Check release placeholders as fatal' \
		'  check-toolchain  Verify wrapper can reach real riscv64-unknown-elf tools' \
		'  import-sdk       Import ../SDK/SDK_CP800X_V1010_20260418'

docker-build:
	docker compose -f docker-dev/compose.yaml build

smoke:
	scripts/recipe_smoke_compile.sh

examples:
	scripts/recipe_smoke_compile_examples.sh

real-examples:
	scripts/real_compile_examples.sh

package:
	scripts/package_platform.sh $(VERSION)

index: package
	python3 scripts/generate_package_index.py --version $(VERSION) --archive package/dist/chippump-cp8000-$(VERSION).tar.gz --url $(PACKAGE_URL) --website-url $(PACKAGE_WEBSITE_URL) --email $(PACKAGE_EMAIL) --help-url $(PACKAGE_HELP_URL)

audit:
	scripts/audit_placeholders.sh

release-audit:
	scripts/audit_placeholders.sh --release

check-toolchain:
	scripts/check_toolchain.sh

import-sdk:
	scripts/import_vendor_sdk.sh ../SDK/SDK_CP800X_V1010_20260418
