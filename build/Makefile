root := $(CARGO_MANIFEST_DIR)
output := $(OUT_DIR)

build := $(root)/build
source := $(build)/source
wrapper := $(build)/wrapper
patches := $(build)/patches

sources := $(filter-out %/main.cc,$(wildcard $(source)/*.cc) $(wildcard $(source)/cacti/*.cc))
objects := $(patsubst $(source)/%.cc,$(output)/%.o,$(sources))

sources := $(wildcard $(wrapper)/*.cc) $(wildcard $(wrapper)/cacti/*.cc)
objects += $(patsubst $(wrapper)/%.cc,$(output)/%.0,$(sources))

ifdef CARGO_FEATURE_CACHE
sources := $(wildcard $(wrapper)/cache/*.cc)
objects += $(patsubst $(wrapper)/%.cc,$(output)/%.0,$(sources))
endif

ifeq ($(shell uname),Darwin)
suffix = dylib
else
suffix = so
endif

NTHREADS ?= 4
flags := -fPIC -O3 -w -msse2 -mfpmath=sse -DNTHREADS=$(NTHREADS) -I$(source) -I$(source)/cacti

$(output)/libmcpat.$(suffix): $(output)/.mkdir $(output)/.patch $(objects)
	$(CXX) $(objects) -shared -o $@

$(output)/%.o: $(source)/%.cc
	$(CXX) $(flags) $< -c -o $@

$(output)/%.0: $(wrapper)/%.cc
	$(CXX) $(flags) $< -I$(build) -c -o $@

$(output)/.mkdir:
	mkdir $(output)/cacti
ifdef CARGO_FEATURE_CACHE
	mkdir $(output)/cache
endif
	touch $@

$(output)/.patch:
ifdef CARGO_FEATURE_CACHE
	(cd $(source); cat $(sort $(wildcard $(patches)/*.patch)) | patch -p1)
endif
	touch $@
