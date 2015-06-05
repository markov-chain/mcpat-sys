build := $(shell pwd)
source := $(build)/source
wrapper := $(build)/wrapper
patches := $(build)/patches

NTHREADS ?= 4
cflags := -fPIC -O3 -w -msse2 -mfpmath=sse -DNTHREADS=$(NTHREADS)
cflags += -I$(source) -I$(source)/cacti -I$(build)
lflags := -shared

sources := $(filter-out %/main.cc,$(wildcard $(source)/*.cc) $(wildcard $(source)/cacti/*.cc))
objects := $(patsubst %.cc,%.o,$(sources))

sources := $(wildcard $(wrapper)/*.cc) $(wildcard $(wrapper)/cacti/*.cc)
objects += $(patsubst %.cc,%.o,$(sources))

ifdef CARGO_FEATURE_CACHE
cflags += -I$(DEP_HIREDIS_ROOT)/include
lflags += -L$(DEP_HIREDIS_ROOT)/lib -lhiredis
sources := $(wildcard $(wrapper)/cache/*.cc)
objects += $(patsubst %.cc,%.o,$(sources))
endif

ifeq ($(shell uname),Darwin)
library = libmcpat.dylib
else
library = libmcpat.so
endif

$(OUT_DIR)/$(library): $(source)/$(library)
	cp $< $@

$(source)/$(library): $(objects)
	$(CXX) $(lflags) $(objects) -o $@

%.o: %.cc | $(source)/.patch
	$(CXX) $(cflags) $< -c -o $@

$(source)/.patch:
ifdef CARGO_FEATURE_CACHE
	(cd $(source); cat $(sort $(wildcard $(patches)/*.patch)) | patch -p1)
endif
	touch $@

.PHONY: $(OUT_DIR)/$(library)
