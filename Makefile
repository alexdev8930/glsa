.PHONY: all configure build run clean linux windows

ifeq ($(OS),Windows_NT)
VCPKG_ROOT ?= C:/vcpkg
PRESET = windows-msvc
BUILD_DIR = build/windows-msvc
RUN_DIR = build/windows-msvc/examples/Debug
RUN_PROGRAM = glsa_demo.exe
else
VCPKG_ROOT ?= $(HOME)/vcpkg
PRESET = linux
BUILD_DIR = build/linux
RUN_DIR = build/linux/examples
RUN_PROGRAM = ./glsa_demo
endif

export VCPKG_ROOT

all: build

linux: PRESET = linux
linux: BUILD_DIR = build/linux
linux: RUN_DIR = build/linux/examples
linux: RUN_PROGRAM = ./glsa_demo
linux: build

windows: PRESET = windows-msvc
windows: BUILD_DIR = build/windows-msvc
windows: RUN_DIR = build/windows-msvc/examples/Debug
windows: RUN_PROGRAM = glsa_demo.exe
windows: build

configure:
	cmake --preset $(PRESET)

build: configure
	cmake --build --preset $(PRESET)

run: build
	cmake -E chdir $(RUN_DIR) $(RUN_PROGRAM)

clean:
	cmake -E rm -rf $(BUILD_DIR)
