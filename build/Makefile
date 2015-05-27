root := $(CARGO_MANIFEST_DIR)
output := $(OUT_DIR)

build := $(root)/build
source := $(build)/source
wrapper := $(build)/wrapper

sources := $(filter-out %/main.cc,$(wildcard $(source)/*.cc) $(wildcard $(source)/cacti/*.cc))
objects := $(patsubst $(source)/%.cc,$(output)/%.o,$(sources))

sources := $(wildcard $(wrapper)/*.cc)
objects += $(patsubst $(wrapper)/%.cc,$(output)/%.0,$(sources))

NTHREADS ?= 4
flags := -fPIC -O3 -w -msse2 -mfpmath=sse -DNTHREADS=$(NTHREADS) -I$(source) -I$(source)/cacti

$(output)/libmcpat.so: $(output)/.setup $(objects)
	$(CXX) $(objects) -shared -o $@

$(output)/%.o: $(source)/%.cc
	$(CXX) $(flags) -c $< -o $@

$(output)/%.0: $(wrapper)/%.cc
	$(CXX) $(flags) -I$(build) -c $< -o $@

$(output)/.setup:
	mkdir $(output)/cacti
	touch $@
