root := $(CARGO_MANIFEST_DIR)
output := $(OUT_DIR)

build := $(root)/build
source := $(build)/source
sources := $(wildcard $(source)/*.cc) $(wildcard $(source)/cacti/*.cc)
sources := $(filter-out %/main.cc,$(sources))
objects := $(patsubst $(source)/%.cc,$(output)/%.o,$(sources))
flags := -fPIC -O3 -msse2 -mfpmath=sse -DNTHREADS=4 -I$(source) -I$(source)/cacti -w

lib: $(output)/libmcpat.so

$(output)/libmcpat.so: $(objects)
	$(CXX) $(objects) -shared -o $@

$(output)/%.o: $(source)/%.cc $(output)/cacti
	$(CXX) $(flags) -c $< -o $@

$(output)/cacti:
	mkdir $@

.PHONY: lib
