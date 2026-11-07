/**
 * @file example.cpp
 *
 * @brief GLSA basic rendering example.
 *
 * @details
 * This example demonstrates the basic setup required to initialize
 * an OpenGL context and use GLSA in a C++ application.
 *
 * The GLSA main header is included and its implementation is enabled
 * through GLSA_IMPLEMENTATION. However, no GLSA functionality is
 * currently used because the public API is still under development
 * and is not yet available for use.
 *
 * This example currently demonstrates:
 * - Including GLSA and enabling its implementation.
 * - Initializing GLFW.
 * - Creating an OpenGL window.
 * - Making the OpenGL context current.
 * - Initializing GLAD.
 * - Executing a basic OpenGL rendering loop.
 * - Cleaning up application resources.
 *
 * @note
 * GLSA requires a valid OpenGL context and initialized OpenGL
 * function loader before its rendering functionality can be used.
 *
 * @note
 * This example uses GLFW for window and context management,
 * and GLAD for OpenGL function loading.
 *
 * @warning
 * This example requires an OpenGL 3.3 Core Profile context
 * to be configured by the application or its build system.
 *
 * @dependencies
 * - GLSA
 * - GLFW
 * - GLAD
 * - GLM
 *
 * @copyright Copyright (c) 2026 AlexDev
 * @license MIT
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define GLSA_IMPLEMENTATION
#include <glsa/glsa.h>

int main() {
    if (glfwInit() == GLFW_FALSE) {
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLSA Demo", nullptr, nullptr);

    if (window == nullptr) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    while (glfwWindowShouldClose(window) == 0) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
