# GLSA API Specification

## Lifecycle

### `glsa::init`

Initializes the GLSA runtime context for the given render size. Before calling it, initialize a valid GLFW window and OpenGL context, load OpenGL function pointers (e.g. via GLAD), and make that context current on the active thread. Returns `true` if the context is valid and dimensions are acceptable. Returns `false` if dimensions are invalid or no OpenGL context is current.

```cpp
struct Extent2D {
    int width;
    int height;
};

bool init(Extent2D initial_extent);
