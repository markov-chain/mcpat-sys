root := $(CARGO_MANIFEST_DIR)
output := $(OUT_DIR)

build := $(root)/build
source := $(build)/source
wrapper := $(build)/wrapper

sources := $(filter-out %/main.cc,$(wildcard $(source)/*.cc) $(wildcard $(source)/cacti/*.cc))
objects := $(patsubst $(source)/%.cc,$(output)/%.o,$(sources))

sources := $(wildcard $(wrapper)/*.cc)
objects += $(patsubst $(wrapper)/%.cc,$(output)/%.0,$(sources))

flags := -fPIC -O3 -w -msse2 -mfpmath=sse -DNTHREADS=4 -I$(source) -I$(source)/cacti

lib: $(output)/libmcpat.so

$(output)/libmcpat.so: $(objects)
	$(CXX) $(objects) -shared -o $@

$(output)/%.o: $(source)/%.cc $(output)/cacti
	$(CXX) $(flags) -c $< -o $@

$(output)/%.0: $(wrapper)/%.cc $(output)/cacti
	$(CXX) $(flags) -I$(build) -I$(wrapper) -c $< -o $@

$(output)/cacti:
	mkdir $@

.PHONY: lib
