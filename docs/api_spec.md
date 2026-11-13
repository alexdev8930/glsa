# GLSA API Specification

## Data Types

### `glsa::Extent2D`
A plain configuration structure holding uniform resolution or viewport layout boundaries.
```cpp
struct Extent2D {
    int width;   // Target width component in pixels or units (> 0)
    int height;  // Target height component in pixels or units (> 0)
};
```

### `glsa::Program`
Opaque handle to a linked OpenGL shader program. The id is zero when the handle is invalid.
```cpp
struct Program {
    unsigned int id = 0;
};
```

### `glsa::ShaderSource`
Container holding vertex and fragment GLSL source strings. Prevents accidentally swapping the two arguments when creating a program.
```cpp
struct ShaderSource {
    std::string_view vertex;   // GLSL vertex shader source
    std::string_view fragment; // GLSL fragment shader source
};
```

## Core API

### `glsa::init`

Initializes the GLSA runtime context for the given render size. Before calling it, initialize a valid GLFW window and OpenGL context, load OpenGL function pointers (e.g. via GLAD), and make that context current on the active thread. Returns `true` if the context is valid and dimensions are acceptable. Returns `false` if dimensions are invalid or no OpenGL context is current.

```cpp
[[nodiscard]] bool init(Extent2D initial_extent);
```

### `glsa::getDefaultExtent`

Returns the default render extent stored during `glsa::init`.

```cpp
Extent2D getDefaultExtent();
```

### `glsa::loadShaderSource`

Loads a shader source file from disk into a string.

```cpp
std::string loadShaderSource(const char* filepath);
```

### `glsa::createProgram`

Compiles and links a vertex and fragment shader into a single OpenGL program. Returns a `Program` handle. The id is zero if compilation or linking failed.

```cpp
[[nodiscard]] Program createProgram(const ShaderSource& sources);
```

### `glsa::useProgram`

Makes the given program the active OpenGL shader program. 

```cpp
void useProgram(const Program& program);
```

### `glsa::deleteProgram` 

Delete a shader program and release its OpenGL resources.

```cpp
void deleteProgram(Program& program);
```

#### `glsa::setUniform(program, name, vec4)`

Sets a 4-component vector uniform. Commonly used for RGBA colors or positions with a `w` component.

```cpp
void setUniform(const Program& program, const char* name, const glm::vec4& value);
```

### `glsa::setUniform(program, name, vec3)`

Sets a 3-component vector uniform. Commonly used for 3D positions, directions, or RGB colors.

```cpp
void setUniform(const Program& program, const char* name, const glm::vec3& value);
```

### `glsa::setUniform(program, name, vec2)`

Sets a 2-component vector uniform. Commonly used for 2D positions, offsets, or UV coordinates.

```cpp
void setUniform(const Program& program, const char* name, const glm::vec2& value);
```

### `glsa::setUniform(program, name, float)`

Sets a single-precision scalar uniform.

```cpp
void setUniform(const Program& program, const char* name, float value);
```

### `glsa::setUniform(program, name, int)`

Sets a signed integer uniform. Commonly used for texture unit indices or shader flags.

```cpp
void setUniform(const Program& program, const char* name, int value);
```

### Predefined Color Constants

All generated constants are normalized RGBA `glm::vec4` values in `[0.0, 1.0]` with an alpha of `1.0f`, including standard web, Pantone (`PAN_*`), and retro hardware palettes (`NES_*`, `MSX_*`, `CGA_*`, `ZXSPEC_*`, `MAC2_*`, `SG1000_*`).

```cpp
#include <glsa/glsa_colors.h>

glsa::setUniform(program, "u_color", glsa::colors::PMS_542);
```

### `glsa::overrideAlpha`

Returns a copy of a color with its alpha channel replaced at compile time.

```cpp
[[nodiscard]] constexpr glm::vec4 overrideAlpha(const glm::vec4& color, float alpha) noexcept;
```

(`GL_BLEND` must be enabled before you call the function)