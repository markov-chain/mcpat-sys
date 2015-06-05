clean-build := $(CARGO_MANIFEST_DIR)/build
dirty-build := $(OUT_DIR)/build
ifdef CARGO_FEATURE_CACHING
dirty-build := $(dirty-build)-caching
endif

all: $(dirty-build)
	$(MAKE) -C $<

$(dirty-build):
	cp -R $(clean-build) $@

.PHONY: all
