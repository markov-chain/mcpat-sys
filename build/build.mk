clean-build := $(CARGO_MANIFEST_DIR)/build
dirty-build := $(OUT_DIR)/build
ifdef CARGO_FEATURE_CACHE
dirty-build := $(dirty-build)-cache
endif

all: $(dirty-build)
	$(MAKE) -C $<

$(dirty-build):
	cp -R $(clean-build) $@

.PHONY: all
