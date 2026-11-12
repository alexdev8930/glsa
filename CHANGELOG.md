# Changelog

The format is based on [Keep a Changelog](https://keepachangelog.com).
Versioning uses [semver](https://semver.org).

## Unreleased

### Added
- Implemented `glsa::setUniform` overloads for `mat4`, `vec4`, `vec3`, `vec2`, `float`, and `int`.
- Implemented `glsa::deleteProgram(Program& program)` to delete a program
- Implemented `glsa::useProgram(const Program& program)` to bind a shader program for drawing.
- Updated `examples/example.cpp` to compile and link inline GLSL shaders via `glsa::createProgram` and render a light blue square.
- Implemented `glsa::createProgram(const ShaderSource& sources)` with vertex and fragment shader compilation, program linking, error logging, and GPU resource cleanup.
- Implemented `glsa::loadShaderSource(const char* filepath)` to read GLSL shader source files from disk into a `std::string`.
- Added internal initialization state tracking (`g_is_initialized`) in `glsa::internal` and `[GLSA ERROR]` logging across runtime validation checks.
- Added `glsa/detail/glsa_internal.h` for internal runtime state and private helpers.

## v0.1.0 - 2026-11-11

### Added
- Added a dedicated public `glsa/glsa_types.h` header file to cleanly house the `Extent2D`, `Program`, and `ShaderSource` structures.
- Added the initial `glsa.h` header scaffold with C++17, platform, and OpenGL version checks, plus the documented `glsa::init` declaration.
- Added a cross-platform CMake `run-examples` target for building and launching the demo.
- Added GitHub Actions builds for Linux, Windows/MSVC and MacOS.
- Enabled both X11 and Wayland GLFW backends on Linux.
- Added a GLFW window example to test the OpenGL and CMake setup.
- Started the API spec with the planned `glsa::init` requirements and return value.
- Added ClangFormat and clangd config files, along with the MIT license and contribution guide.
- Implemented `glsa::init(Extent2D initial_extent)` with dimension validation and OpenGL context check.
- Added `glsa::getDefaultExtent()` accessor for retrieving the cached default render extent.
- Configured clang-format to indent preprocessor directives with spaces.
- Added clang-tidy to CMake when it is installed.
- Added GLFW, window creation, and GLAD initialization checks to the example.
- Added forward-compatible OpenGL 4.1 core context request on macOS.
- Added vcpkg preset configuration for CMake presets without requiring `VCPKG_ROOT`.
- Added CMake preset documentation to the README.
- Added header-only and dependency rules for contributions to CONTRIBUTING.md.
- Added ignore rules for local clangd and compile command files.
- Added `[[nodiscard]]` on `init` and documentation for `getDefaultExtent` to `docs/api_spec.md`.
- Added `glsa::init({800, 600})` call to `examples/example.cpp`.
