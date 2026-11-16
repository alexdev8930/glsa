/**
 * @file example.cpp
 *
 * @brief GLSA basic example.
 *
 * @details
 * This example demonstrates the basic setup required to initialize
 * an OpenGL context and use GLSA in a C++ application.
 *
 * This example currently demonstrates:
 * - Initializing GLFW.
 * - Creating an OpenGL window.
 * - Making the OpenGL context current.
 * - Initializing GLAD.
 * - Initializing GLSA.
 * - Querying the active render aspect ratio via glsa::getAspectRatio.
 * - Compiling and linking inline GLSL shaders via GLSA.
 * - Uploading vertex data to a GPU buffer via glsa::Buffer and glsa::setBufferData.
 * - Configuring vertex attribute layouts via glsa::setVertexAttribPointer.
 * - Setting shader uniforms via glsa::setUniform.
 * - Executing a basic OpenGL rendering loop to draw a colored triangle.
 * - Cleaning up OpenGL and application resources.
 *
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

    GLFWwindow* window = glfwCreateWindow(800, 600, "GLSA Demo", nullptr, nullptr);

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

    const char* vertex_shader_src = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    const char* fragment_shader_src = R"(
        #version 330 core
        uniform vec4 uColor;
        out vec4 FragColor;
        void main() {
            FragColor = uColor;
        }
    )";

    const float aspect = glsa::getAspectRatio();

    const std::array<glm::vec3, 3> triangle = {
        glm::vec3(-0.5f / aspect, -0.433f, 0.0f),
        glm::vec3(0.5f / aspect, -0.433f, 0.0f),
        glm::vec3(0.0f, 0.433f, 0.0f),
    };
    
    glsa::VertexArray vao = glsa::createVertexArray();
    glsa::bindVertexArray(vao);

    glsa::Buffer vbo = glsa::createBuffer();
    glsa::setBufferData(vbo, triangle);
    glsa::setVertexAttribPointer(0, {3, sizeof(glm::vec3), 0});

    glsa::Program program = glsa::createProgram({vertex_shader_src, fragment_shader_src});
    if (program.id == 0) {
        glsa::deleteBuffer(vbo);
        glsa::deleteVertexArray(vao);
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    while (glfwWindowShouldClose(window) == 0) {
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glsa::useProgram(program);
        glsa::setUniform(program, "uColor", glsa::colors::PMS_542);
        glsa::bindVertexArray(vao);
        glsa::drawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glsa::deleteBuffer(vbo);
    glsa::deleteVertexArray(vao);
    glsa::deleteProgram(program);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
