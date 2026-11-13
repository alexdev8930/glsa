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

### `glsa::VertexArray`

Opaque handle to a vertex array object. The id is zero when the handle is invalid.

```cpp
struct VertexArray {
    unsigned int id = 0;
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

### `glsa::createVertexArray`

Creates a vertex array object. Returns `VertexArray{0}` if initialization has not been called.

```cpp
[[nodiscard]] VertexArray createVertexArray();
```

### `glsa::bindVertexArray`

Binds a vertex array object for subsequent drawing.

```cpp
void bindVertexArray(const VertexArray& vao);
```

### `glsa::deleteVertexArray`

Deletes a vertex array object and releases its OpenGL resources. Resets `id` to `0`.

```cpp
void deleteVertexArray(VertexArray& vao);
```

### `glsa::drawArrays`

Draws primitives from array data. Wraps `glDrawArrays`.

```cpp
void drawArrays(GLenum mode, GLint first, GLsizei count);
```