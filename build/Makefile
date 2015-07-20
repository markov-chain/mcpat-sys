build := $(shell pwd)
source := $(build)/source
wrapper := $(build)/wrapper
patches := $(build)/patches

FILTER_OUT = $(foreach v,$(2),$(if $(findstring $(1),$(v)),,$(v)))

NTHREADS ?= 4
cflags := -fPIC -O3 -w -msse2 -mfpmath=sse -DNTHREADS=$(NTHREADS)
cflags += -I$(source) -I$(source)/cacti -I$(build)
lflags := -shared

sources := $(call FILTER_OUT,main.cc,$(wildcard $(source)/*.cc) $(wildcard $(source)/cacti/*.cc))
objects := $(patsubst %.cc,%.o,$(sources))
patches := $(sort $(wildcard $(patches)/*.patch))

sources := $(wildcard $(wrapper)/*.cc) $(wildcard $(wrapper)/cacti/*.cc)
objects += $(patsubst %.cc,%.o,$(sources))

ifdef CARGO_FEATURE_CACHING
cflags += -I$(DEP_HIREDIS_ROOT)/include
lflags += -Wl,-rpath,$(DEP_HIREDIS_ROOT)/lib -L$(DEP_HIREDIS_ROOT)/lib -lhiredis
sources := $(wildcard $(wrapper)/caching/*.cc)
objects += $(patsubst %.cc,%.o,$(sources))
else
patches := $(call FILTER_OUT,caching,$(patches))
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
	(cd $(source); cat $(patches) | patch -p1)
	touch $@

.PHONY: $(OUT_DIR)/$(library)
