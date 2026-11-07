# Define standard configuration variables
COMPILER_FLAGS = -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
GENERATOR_FLAGS = -G Ninja

.PHONY: all configure build run clean

all: build

configure:
	cmake -S . -B build $(GENERATOR_FLAGS) $(COMPILER_FLAGS)

build:
	@if [ ! -d "build" ]; then \
		make configure; \
	fi
	cmake --build build

run: build
	./build/examples/glsa_demo

clean:
	rm -rf build/
