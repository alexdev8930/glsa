# Changelog

The format is based on [Keep a Changelog](https://keepachangelog.com).
Versioning uses [semver](https://semver.org).


## v1.1.0 - 2026-11-22

### Added
- Implemented `"mvp"` GLSL preset in `glsa::shaderPreset(std::string_view name, int version)` with `uMVP` (`mat4`) transform support.
- Implemented `glsa::drawRectangle(int, int, int, int, const glm::vec4&)` overload in `glsa/glsa.h` for rendering 2D rectangles in screen pixel coordinates with a top-left origin.
- Implemented `glsa::drawRectangle(glm::vec2, glm::vec2, const glm::vec4&)` and `glsa::drawCircle(glm::vec2, float, const glm::vec4&, int)` immediate 2D shape helpers in `glsa/glsa.h`.
- Added `ShapeRendererState` and `g_shape_renderer` in `glsa/detail/glsa_internal.h` to cache internal GPU resources for 2D shape helpers.
- Added `examples/basic_shapes.cpp` (`glsa_basic_shapes` target) demonstrating immediate rectangle and circle rendering.
- Implemented `glsa::drawElements(GLenum, GLsizei, GLenum, const void*)` to wrap `glDrawElements`.
- Implemented `glsa::shaderPreset(std::string_view name, int version)` in `glsa/glsa.h` with built-in `"basic"`, `"vertex_color"`, `"gradient"`, and `"pulse"` GLSL presets.
- Added `glsa::Buffer` opaque handle type in `glsa/glsa_types.h`.
- Implemented `glsa::createBuffer()`, `glsa::bindBuffer()`, `glsa::setBufferData()`, and `glsa::deleteBuffer()` for GPU buffer object management.
- Added `glsa::VertexAttribute` layout struct in `glsa/glsa_types.h`.
- Implemented `glsa::setVertexAttribPointer(GLuint, const VertexAttribute&)` to configure and enable vertex attribute pointers.
- Implemented `glsa::getAspectRatio()` to compute the aspect ratio from the default render extent.
- Updated `examples/example.cpp` to upload triangle vertex data via `glsa::Buffer` and render an aspect-corrected triangle.

### Changed
- Updated `Makefile` `run` target to support selecting an executable via `EXAMPLE=<target>` (defaults to `glsa_demo`).
- Replaced `glfwGetCurrentContext()` in `glsa::init()` with a direct OpenGL `glGetString(GL_VERSION)` check, removing GLFW as a hard dependency.
- Removed redundant zero-ID check in `glsa::deleteVertexArray()`.
- Disabled `performance-no-int-to-ptr` in `.clang-tidy` to allow standard OpenGL 3.3 byte-offset casts.

## v1.0.0 - 2026-11-12

### Added
- Implemented `glsa::drawArrays(GLenum, GLint, GLsizei)` to wrap `glDrawArrays`.
- Added `glsa::VertexArray` opaque handle type in `glsa/glsa_types.h`.
- Implemented `glsa::createVertexArray()`, `glsa::bindVertexArray()`, and `glsa::deleteVertexArray()` for vertex array object management.
- Added a standalone header providing predefined `inline constexpr glm::vec4` RGBA color constants under `namespace glsa::colors`. 
- Added a `glsa::overrideAlpha(const glm::vec4& color, float alpha)` helper in `glsa_colors.h` to replace the alpha channel of any `glm::vec4` color.
- Added `tools/color_gen/json_to_header.py`, `tools/color_gen/lots_of_colors.json` to generate `glsa_colors.h` automatically.
- Implemented `glsa::setUniform` overloads for `mat4`, `vec4`, `vec3`, `vec2`, `float`, and `int`.
- Implemented `glsa::deleteProgram(Program& program)` to delete a program.
- Implemented `glsa::useProgram(const Program& program)` to bind a shader program for drawing.
- Updated `examples/example.cpp` to compile and link inline GLSL shaders via `glsa::createProgram` and render a light blue square.
- Implemented `glsa::createProgram(const ShaderSource& sources)` with vertex and fragment shader compilation, program linking, error logging, and GPU resource cleanup.
- Implemented `glsa::loadShaderSource(const char* filepath)` to read GLSL shader source files from disk into a `std::string`.
- Added internal initialization state tracking (`g_is_initialized`) in `glsa::internal` and `[GLSA ERROR]` logging across runtime validation checks.
- Added `glsa/detail/glsa_internal.h` for internal runtime state and private helpers.

### Changed
- Disabled `readability-uppercase-literal-suffix` to allow lowercase `f` float literals

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
