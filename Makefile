# Makefile wrapper for GLSA
ifeq ($(OS),Windows_NT)
    PLATFORM ?= windows-msvc
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        PLATFORM ?= macos
    else
        PLATFORM ?= linux
    endif
endif

EXAMPLE ?= glsa_basic_shapes

.PHONY: all linux windows-msvc macos clean run

all: $(PLATFORM)

linux:
	@cmake --preset linux && cmake --build --preset linux

windows-msvc:
	@cmake --preset windows-msvc && cmake --build --preset windows-msvc

macos:
	@cmake --preset macos && cmake --build --preset macos

clean:
	@rm -rf build
	@echo "Build artifacts cleaned."

run:
	@case "$(PLATFORM)" in \
	linux) \
		if [ -f "build/linux/examples/$(EXAMPLE)" ]; then \
			./build/linux/examples/$(EXAMPLE); \
		else \
			echo "Error: Linux build not found ($(EXAMPLE))."; \
			exit 1; \
		fi; \
		;; \
	windows-msvc) \
		if [ -f "build/windows-msvc/examples/$(EXAMPLE).exe" ]; then \
			./build/windows-msvc/examples/$(EXAMPLE).exe; \
		else \
			echo "Error: Windows build not found ($(EXAMPLE).exe)."; \
			exit 1; \
		fi; \
		;; \
	macos) \
		if [ -f "build/macos/examples/$(EXAMPLE)" ]; then \
			./build/macos/examples/$(EXAMPLE); \
		else \
			echo "Error: macOS build not found ($(EXAMPLE))."; \
			exit 1; \
		fi; \
		;; \
	*) \
		echo "Error: Unknown platform '$(PLATFORM)'."; \
		exit 1; \
		;; \
	esac
