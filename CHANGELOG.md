# Changelog

The format is based on [Keep a Changelog](https://keepachangelog.com).
Versioning uses [semver](https://semver.org).

## [Unreleased]

### Added
- Added the initial `glsa.h` header scaffold with C++17, platform, and OpenGL version checks, plus the documented `glsa::init` declaration.
- Added a cross-platform CMake `run-examples` target for building and launching the demo.
- Added GitHub Actions builds for Linux and Windows/MSVC.
- Enabled both X11 and Wayland GLFW backends on Linux.
- Added a GLFW window example to test the OpenGL and CMake setup.
- Started the API spec with the planned `glsa::init` requirements and return value.
- Added ClangFormat and clangd config files, along with the MIT license and contribution guide.

### Changed
- Configured clang-format to indent preprocessor directives with spaces.
- CMake now runs clang-tidy when it is installed.
- The example checks GLFW, window creation, and GLAD initialization before continuing.
- CMake presets locate vcpkg in the standard per-user directory without requiring a `VCPKG_ROOT` export.
- The README now documents CMake preset commands for building and running the demo.
- Clarified the header-only and dependency rules for contributions.
- Updated ignore rules for local clangd and compile command files.
