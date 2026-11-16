/**
 * @file basic_shapes.cpp
 *
 * @brief GLSA immediate 2D shapes example.
 *
 * @details
 * This example demonstrates how to draw 2D rectangles and circles in GLSA
 * without manually setting up vertex arrays, buffers, or shaders.
 *
 * This example currently demonstrates:
 * - Initializing GLFW, GLAD, and GLSA.
 * - Querying the active render aspect ratio via glsa::getAspectRatio.
 * - Drawing solid rectangles via glsa::drawRectangle.
 * - Drawing aspect-corrected circles via glsa::drawCircle.
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

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define GLSA_IMPLEMENTATION
#include <glsa/glsa.h>
#include <glsa/glsa_colors.h>

int main() {
    if (glfwInit() == GLFW_FALSE) {
        return -1;
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "GLSA Basic Shapes", nullptr, nullptr);

    if (window == nullptr) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress)) == 0) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    if (!glsa::init({800, 600})) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    const float aspect = glsa::getAspectRatio();

    while (glfwWindowShouldClose(window) == 0) {
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw an aspect-corrected square on the left
        glsa::drawRectangle({-0.45f, 0.0f}, {0.4f / aspect, 0.4f}, glsa::colors::PMS_178);

        // Draw an aspect-corrected circle on the right
        glsa::drawCircle({0.45f, 0.0f}, 0.22f, glsa::colors::PMS_542);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
