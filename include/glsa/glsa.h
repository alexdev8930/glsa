/**
 * @file glsa.h
 * @brief Main library header for GLSA (Graphics Library Shader API).
 *
 * @details
 * GLSA is a modern, lightweight, header-only C++ OpenGL abstraction framework.
 * It eliminates boilerplate context management, handles multi-platform
 * target fallbacks natively, and maps pipeline commands directly to clean C++ structures.
 *
 * @note
 * This library enforces a strict C++17 language floor across all compilers.
 *
 * @warning
 * This library requires an OpenGL 3.3 to 4.6 Core Profile context
 * to be configured by the application or its build system for Linux / Windows and OpenGL 3.3 to 4.1
 * for Apple macos.
 *
 * @dependencies
 * - GLFW
 *
 * @copyright Copyright (c) 2026 AlexDev
 * @license MIT
 */

#ifndef GLSA_GLSA_H
#define GLSA_GLSA_H

#include <cstddef>
#include <cstdio>
#include <fstream>
#include <string>
#include <glm/glm.hpp>
#include "glsa_types.h"

/* MSVC doesn't update __cplusplus by default, so we check _MSVC_LANG instead */
#if defined(_MSVC_LANG)
    #define GLSA_CPLUSPLUS _MSVC_LANG
#else
    #define GLSA_CPLUSPLUS __cplusplus
#endif

/* Fail early if the compiler isn't set to C++17 or newer */
#if GLSA_CPLUSPLUS < 201703L
    #error "GLSA requires C++17 or newer."
#endif

#undef GLSA_CPLUSPLUS

/* Figure out what OS we are building on */
#if defined(_WIN32)
    #define GLSA_PLATFORM_WINDOWS 1
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if TARGET_OS_OSX
        #define GLSA_PLATFORM_MACOS 1
    #else
        #error "GLSA only supports macOS on Apple platforms (iOS/tvOS/watchOS not supported)."
    #endif
#elif defined(__ANDROID__)
    #error "GLSA does not support Android."
#elif defined(__linux__)
    #define GLSA_PLATFORM_LINUX 1
#else
    #error "GLSA does not support this platform."
#endif

/* Set max OpenGL versions (Mac is locked to 4.1, PC gets 4.6) */
#if defined(GLSA_PLATFORM_MACOS)
    #define GLSA_MAX_GL_MAJOR 4
    #define GLSA_MAX_GL_MINOR 1
#elif defined(GLSA_PLATFORM_WINDOWS) || defined(GLSA_PLATFORM_LINUX)
    #define GLSA_MAX_GL_MAJOR 4
    #define GLSA_MAX_GL_MINOR 6
#endif


/* GLSA Public API functions */
namespace glsa {


/**
 * @brief Initializes the GLSA runtime context with initial rendering bounds.
 *
 * @param initial_extent The initial configuration dimensions (width and height) of the target
 * rendering area.
 *
 * @pre A valid OpenGL context must be made current on the active thread, and an external OpenGL
 *      function loader (such as GLAD or GLEW) MUST have successfully resolved function pointers
 *      before calling this function.
 *
 * @return true  If the provided dimensions are valid and a valid OpenGL context is
 *              current on the active thread.
 * @return false If width or height are invalid (<= 0), or if no OpenGL context is
 *              current on the active thread.
 */
[[nodiscard]] bool init(Extent2D initial_extent);


/**
 * @brief Retrieves the default rendering extent configured during initialization.
 * @pre glsa::init() must have been called successfully first.
 * @return The cached Extent2D structure containing width and height bounds.
 */
Extent2D getDefaultExtent();


/**
 * @brief Load a shader source file from disk into a string.
 *
 * @param filepath Path to the shader source file (e.g. "shaders/basic.vert").
 * @return The file contents as a string, or an empty string if the file could not be read.
 */
std::string loadShaderSource(const char* filepath);


/**
 * @brief Compile and link a shader program from vertex and fragment source.
 *
 * @param sources Container holding the vertex and fragment GLSL source views.
 *
 * @return A Program handle. id is 0 if compilation or linking failed;
 *         check the console for the shader compiler/linker log.
 *
 * @pre glsa::init() must have been called successfully first.
 */
[[nodiscard]] Program createProgram(const ShaderSource& sources);


/**
 * @brief Bind a shader program for subsequent drawing.
 *
 * Makes the given program the active OpenGL shader program. All subsequent
 * uniform updates and draw calls will use this program until another one is
 * bound.
 *
 * @param program The program to bind. Must be a valid handle (non-zero id)
 *                returned by glsa::createProgram().
 *
 * @pre glsa::init() must have been called successfully first.
 * @pre program.id must be non-zero (a valid, linked program).
 */
void useProgram(const Program& program);


/**
 * @brief Delete a shader program and release its OpenGL resources.
 *
 * After this call the handle's id is reset to zero, making it safe to
 * call again on the same handle.
 *
 * @param program The program to destroy. Its id is set to 0 after deletion.
 *
 * @pre glsa::init() must have been called successfully first.
 * @post program.id == 0
 */
void deleteProgram(Program& program);


/**
 * @brief Set a uniform mat4 on the currently bound program.
 *
 * @param program The program whose uniform to set (must be bound via useProgram).
 * @param name    Uniform variable name in the shader.
 * @param value   Matrix value.
 */
void setUniform(const Program& program, const char* name, const glm::mat4& value);

/**
 * @brief Set a uniform vec4 on the currently bound program.
 *
 * @param program The program whose uniform to set (must be bound via useProgram).
 * @param name    Uniform variable name in the shader.
 * @param value   Vector value.
 */
void setUniform(const Program& program, const char* name, const glm::vec4& value);

/**
 * @brief Set a uniform vec3 on the currently bound program.
 *
 * @param program The program whose uniform to set (must be bound via useProgram).
 * @param name    Uniform variable name in the shader.
 * @param value   Vector value.
 */
void setUniform(const Program& program, const char* name, const glm::vec3& value);

/**
 * @brief Set a uniform vec2 on the currently bound program.
 *
 * @param program The program whose uniform to set (must be bound via useProgram).
 * @param name    Uniform variable name in the shader.
 * @param value   Vector value.
 */
void setUniform(const Program& program, const char* name, const glm::vec2& value);

/**
 * @brief Set a uniform float on the currently bound program.
 *
 * @param program The program whose uniform to set (must be bound via useProgram).
 * @param name    Uniform variable name in the shader.
 * @param value   Scalar value.
 */
void setUniform(const Program& program, const char* name, float value);

/**
 * @brief Set a uniform int on the currently bound program.
 *
 * @param program The program whose uniform to set (must be bound via useProgram).
 * @param name    Uniform variable name in the shader.
 * @param value   Scalar value.
 */
void setUniform(const Program& program, const char* name, int value);


/**
 * @brief Create a vertex array object.
 *
 * @return A VertexArray handle. id is 0 if creation failed.
 *
 * @pre glsa::init() must have been called successfully first.
 */
[[nodiscard]] VertexArray createVertexArray();

/**
 * @brief Bind a vertex array object for subsequent drawing.
 *
 * @param vao The vertex array object to bind. Must be a valid handle (non-zero id).
 *
 * @pre glsa::init() must have been called successfully first.
 */
void bindVertexArray(const VertexArray& vao);

/**
 * @brief Delete a vertex array object and release its OpenGL resources.
 *
 * After this call the handle's id is reset to zero.
 *
 * @param vao The vertex array object to destroy. Its id is set to 0 after deletion.
 *
 * @pre glsa::init() must have been called successfully first.
 * @post vao.id == 0
 */
void deleteVertexArray(VertexArray& vao);


/**
 * @brief Draw primitives from array data.
 *
 * @param mode  Primitive type (e.g. GL_POINTS, GL_TRIANGLES).
 * @param first Starting index in the enabled arrays.
 * @param count Number of indices to be rendered.
 *
 * @pre glsa::init() must have been called successfully first.
 */
void drawArrays(GLenum mode, GLint first, GLsizei count);

} // namespace glsa


// clang-format off
#if defined(GLSA_IMPLEMENTATION) || defined(GLSA_CLANGD_IMPLEMENTATION)

#include <GLFW/glfw3.h>
#include "glsa/detail/glsa_internal.h"
#include <glm/gtc/type_ptr.hpp>
// clang-format on

namespace glsa {

[[nodiscard]] bool init(Extent2D initial_extent) {
    if (initial_extent.width <= 0 || initial_extent.height <= 0) {
        std::fprintf(
            stderr,
            "[GLSA ERROR] Invalid initial extent (%d x %d). Width and height must be > 0.\n",
            initial_extent.width, initial_extent.height);
        return false;
    }

    if (glfwGetCurrentContext() == nullptr) {
        std::fprintf(stderr,
                     "[GLSA ERROR] No active OpenGL context found on the current thread.\n");
        return false;
    }

    glsa::internal::g_default_extent = initial_extent;
    glsa::internal::g_is_initialized = true;
    return true;
}



Extent2D getDefaultExtent() {
    return glsa::internal::g_default_extent;
}


std::string loadShaderSource(const char* filepath) {
    if (filepath == nullptr) {
        std::fprintf(stderr, "[GLSA ERROR] Shader filepath cannot be null.\n");
        return "";
    }

    std::ifstream file(filepath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::fprintf(stderr, "[GLSA ERROR] Failed to open shader file: %s\n", filepath);
        return "";
    }

    std::streamsize size = file.tellg();
    if (size <= 0) {
        return "";
    }

    std::string source(static_cast<size_t>(size), '\0');
    file.seekg(0, std::ios::beg);

    if (!file.read(source.data(), size)) {
        std::fprintf(stderr, "[GLSA ERROR] Failed to read shader file: %s\n", filepath);
        return "";
    }

    return source;
}


[[nodiscard]] Program createProgram(const ShaderSource& sources) {
    if (!glsa::internal::g_is_initialized) {
        std::fprintf(
            stderr,
            "[GLSA ERROR] Library must be initialized via glsa::init() before calling this "
            "function.\n");
        return Program{0};
    }

    if (glfwGetCurrentContext() == nullptr) {
        std::fprintf(stderr,
                     "[GLSA ERROR] No active OpenGL context found on the current thread.\n");
        return Program{0};
    }

    if (sources.vertex.empty() || sources.fragment.empty()) {
        std::fprintf(stderr, "[GLSA ERROR] Vertex and fragment shader sources cannot be empty.\n");
        return Program{0};
    }

    auto compile_shader = [](GLenum type, std::string_view source) -> GLuint {
        GLuint shader = glCreateShader(type);

        if (shader == 0) {
            std::fprintf(stderr, "[GLSA ERROR] Failed to allocate shader object\n");
            return 0;
        }

        const char* src_ptr = source.data();
        const auto src_len = static_cast<GLint>(source.size());

        glShaderSource(shader, 1, &src_ptr, &src_len);
        glCompileShader(shader);
        GLint success = GL_FALSE;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (success == GL_FALSE) {
            GLint log_len = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
            std::string log(static_cast<size_t>(log_len), '\0');
            glGetShaderInfoLog(shader, log_len, nullptr, log.data());
            const char* stage = (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment";
            std::fprintf(stderr, "[GLSA ERROR] %s shader compilation failed:\n%s\n", stage,
                         log.c_str());
            glDeleteShader(shader);
            return 0;
        }

        return shader;
    };

    GLuint vertex = compile_shader(GL_VERTEX_SHADER, sources.vertex);

    if (vertex == 0) {
        return Program{0};
    }

    GLuint fragment = compile_shader(GL_FRAGMENT_SHADER, sources.fragment);

    if (fragment == 0) {
        glDeleteShader(vertex);
        return Program{0};
    }

    GLuint program = glCreateProgram();
    if (program == 0) {
        std::fprintf(stderr, "[GLSA ERROR] Failed to allocate shader program.\n");
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return Program{0};
    }
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glDetachShader(program, vertex);
    glDetachShader(program, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    GLint success = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (success == GL_FALSE) {
        GLint log_len = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
        std::string log(static_cast<size_t>(log_len), '\0');
        glGetProgramInfoLog(program, log_len, nullptr, log.data());
        std::fprintf(stderr, "[GLSA ERROR] Shader program linking failed:\n%s\n", log.c_str());
        glDeleteProgram(program);
        return Program{0};
    }

    return Program{program};
}


void useProgram(const Program& program) {
    if (!glsa::internal::g_is_initialized) {
        std::fprintf(stderr,
                     "[GLSA ERROR] Library must be initialized via glsa::init() before calling "
                     "this function.\n");
        return;
    }

    if (program.id == 0) {
        std::fprintf(stderr, "[GLSA ERROR] Cannot use invalid program (id == 0).\n");
        return;
    }

    glUseProgram(program.id);
}


void deleteProgram(Program& program) {
    if (!glsa::internal::g_is_initialized) {
        std::fprintf(stderr,
                     "[GLSA ERROR] Library must be initialized via glsa::init() before calling "
                     "this function.\n");
        return;
    }

    if (program.id == 0) {
        return;
    }

    glDeleteProgram(program.id);
    program.id = 0;
}


void setUniform(const Program& program, const char* name, const glm::mat4& value) {
    if (program.id == 0) {
        std::fprintf(stderr, "[GLSA ERROR] Cannot set uniform on invalid program (id == 0).\n");
        return;
    }
    GLint location = glGetUniformLocation(program.id, name);
    if (location == -1) {
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void setUniform(const Program& program, const char* name, const glm::vec4& value) {
    if (program.id == 0) {
        std::fprintf(stderr, "[GLSA ERROR] Cannot set uniform on invalid program (id == 0).\n");
        return;
    }
    GLint location = glGetUniformLocation(program.id, name);
    if (location == -1) {
        return;
    }
    glUniform4fv(location, 1, glm::value_ptr(value));
}

void setUniform(const Program& program, const char* name, const glm::vec3& value) {
    if (program.id == 0) {
        std::fprintf(stderr, "[GLSA ERROR] Cannot set uniform on invalid program (id == 0).\n");
        return;
    }
    GLint location = glGetUniformLocation(program.id, name);
    if (location == -1) {
        return;
    }
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void setUniform(const Program& program, const char* name, const glm::vec2& value) {
    if (program.id == 0) {
        std::fprintf(stderr, "[GLSA ERROR] Cannot set uniform on invalid program (id == 0).\n");
        return;
    }
    GLint location = glGetUniformLocation(program.id, name);
    if (location == -1) {
        return;
    }
    glUniform2fv(location, 1, glm::value_ptr(value));
}

void setUniform(const Program& program, const char* name, float value) {
    if (program.id == 0) {
        std::fprintf(stderr, "[GLSA ERROR] Cannot set uniform on invalid program (id == 0).\n");
        return;
    }
    GLint location = glGetUniformLocation(program.id, name);
    if (location == -1) {
        return;
    }
    glUniform1f(location, value);
}

void setUniform(const Program& program, const char* name, int value) {
    if (program.id == 0) {
        std::fprintf(stderr, "[GLSA ERROR] Cannot set uniform on invalid program (id == 0).\n");
        return;
    }
    GLint location = glGetUniformLocation(program.id, name);
    if (location == -1) {
        return;
    }
    glUniform1i(location, value);
}


[[nodiscard]] VertexArray createVertexArray() {
    if (!glsa::internal::g_is_initialized) {
        std::fprintf(stderr,
                     "[GLSA ERROR] Library must be initialized via glsa::init() before calling "
                     "this function.\n");
        return VertexArray{0};
    }

    VertexArray vao;
    glGenVertexArrays(1, &vao.id);
    return vao;
}

void bindVertexArray(const VertexArray& vao) {
    if (!glsa::internal::g_is_initialized) {
        std::fprintf(stderr,
                     "[GLSA ERROR] Library must be initialized via glsa::init() before calling "
                     "this function.\n");
        return;
    }

    if (vao.id == 0) {
        std::fprintf(stderr, "[GLSA ERROR] Cannot bind invalid vertex array (id == 0).\n");
        return;
    }

    glBindVertexArray(vao.id);
}

void deleteVertexArray(VertexArray& vao) {
    if (!glsa::internal::g_is_initialized) {
        std::fprintf(stderr,
                     "[GLSA ERROR] Library must be initialized via glsa::init() before calling "
                     "this function.\n");
        return;
    }

    if (vao.id == 0) {
        return;
    }

    glDeleteVertexArrays(1, &vao.id);
    vao.id = 0;
}


void drawArrays(GLenum mode, GLint first, GLsizei count) {
    if (!glsa::internal::g_is_initialized) {
        std::fprintf(stderr,
                     "[GLSA ERROR] Library must be initialized via glsa::init() before calling "
                     "this function.\n");
        return;
    }

    glDrawArrays(mode, first, count);
}

} // namespace glsa

#endif // GLSA_IMPLEMENTATION || GLSA_CLANGD_IMPLEMENTATION

#undef GLSA_PLATFORM_WINDOWS
#undef GLSA_PLATFORM_MACOS
#undef GLSA_PLATFORM_LINUX
#undef GLSA_MAX_GL_MAJOR
#undef GLSA_MAX_GL_MINOR

#endif // GLSA_GLSA_H