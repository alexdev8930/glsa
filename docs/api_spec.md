# GLSA API Specification

## Lifecycle

### `glsa::init`

Initializes GLSA's rendering resources for the given render size. Call it after creating and activating an OpenGL context and initializing GLAD. Returns `true` on success and `false` if initialization fails.

```cpp
GLSA_API bool init(int width, int height);
```