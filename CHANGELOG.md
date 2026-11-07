# Changelog

The format is based on [Keep a Changelog](https://keepachangelog.com).
Versioning uses [semver](https://semver.org).

## [Unreleased]

### Added
- Added a Makefile with `configure`, `build`, `run`, and `clean` targets.
- Added a GLFW window example to test the OpenGL and CMake setup.
- Started the API spec with the planned `glsa::init` requirements and return value.
- Added ClangFormat and clangd config files, along with the MIT license and contribution guide.

### Changed
- CMake now runs clang-tidy when it is installed.
- The example checks GLFW, window creation, and GLAD initialization before continuing.
- The README now uses `make run` for the example build and run instructions.
- Clarified the header-only and dependency rules for contributions.
- Updated ignore rules for local clangd and compile command files.
