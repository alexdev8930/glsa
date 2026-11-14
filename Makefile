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
		if [ -f "build/linux/examples/glsa_demo" ]; then \
			./build/linux/examples/glsa_demo; \
		else \
			echo "Error: Linux build not found."; \
			exit 1; \
		fi; \
		;; \
	windows-msvc) \
		if [ -f "build/windows-msvc/examples/glsa_demo.exe" ]; then \
			./build/windows-msvc/examples/glsa_demo.exe; \
		else \
			echo "Error: Windows build not found."; \
			exit 1; \
		fi; \
		;; \
	macos) \
		if [ -f "build/macos/examples/glsa_demo" ]; then \
			./build/macos/examples/glsa_demo; \
		else \
			echo "Error: macOS build not found."; \
			exit 1; \
		fi; \
		;; \
	*) \
		echo "Error: Unknown platform '$(PLATFORM)'."; \
		exit 1; \
		;; \
	esac
