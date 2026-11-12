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