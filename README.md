# GLSA (Graphics Library Shader API)

GLSA is a C++ rendering library built on OpenGL. It provides functions for drawing graphics without requiring you to write shader code for each task. OpenGL is still required to run a GLSA program; GLSA handles the shaders behind the rendering functions it provides.

## What it gives you

- Single-header C++ API
- Render through C++ functions without writing shader code yourself
- Built-in helpers for common shapes like circles and rectangles (3D later)
- Less boilerplate for common rendering tasks
- Clean `glsa::` namespace
- A fast path for custom graphics work without writing everything from scratch

## Project layout

This repo is intentionally small. Most of the work lives in one header:

- `include/glsa/glsa.h` - the main header

> [!NOTE]
> The main header file is still being built so the GLSA API is not usable yet.

## Quick start (Once the main header file has a basic implementation)

Define `GLSA_IMPLEMENTATION` in one C++ file, usually `main.cpp`, before including the header. That injects the implementation code where it belongs.

```cpp
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>   

#define GLSA_IMPLEMENTATION
#include <glsa/glsa.h>

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLSA Demo", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glsa::init(800, 600);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glsa::drawCircle(400.0f, 300.0f, 75.0f, glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glsa::shutdown();
    glfwTerminate();
    return 0;
}
```

## Requirements

- C++17 or newer
- OpenGL 3.3 Core Profile or newer
- GLAD 


