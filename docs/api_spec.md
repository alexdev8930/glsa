# GLSA API Specification

## Lifecycle

### `glsa::init`

Initializes the GLSA runtime context and loads OpenGL function pointers for the given render size. Before calling it, initialize a valid GLFW window and OpenGL context, then make that context current on the active thread. Returns `true` if GLAD loads the function addresses successfully and the driver context satisfies the supported core OpenGL version limits. Returns `false` if function address loading fails or the driver version is below the minimum supported threshold.

```cpp
bool init(int width, int height);
```