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
 * @brief Get the aspect ratio (width / height) of the default render extent.
 *
 * @return Aspect ratio as a float, or 1.0f if not initialized.
 *
 * @pre glsa::init() must have been called successfully first.
 */
[[nodiscard]] float getAspectRatio();

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


/**
 * @brief Create a GPU buffer object.
 *
 * @param target Buffer binding target (defaults to GL_ARRAY_BUFFER).
 * @return A Buffer handle. id is 0 if creation failed.
 *
 * @pre glsa::init() must have been called successfully first.
 */
[[nodiscard]] Buffer createBuffer(GLenum target = GL_ARRAY_BUFFER);

/**
 * @brief Bind a buffer object to its target.
 *
 * @param buffer The buffer object to bind. Must be a valid handle (non-zero id).
 *
 * @pre glsa::init() must have been called successfully first.
 */
void bindBuffer(const Buffer& buffer);

/**
 * @brief Upload raw byte data to a buffer object.
 *
 * @param buffer The target buffer object.
 * @param data   Pointer to the source bytes in CPU memory.
 * @param size   Number of bytes to upload.
 * @param usage  Expected usage pattern (defaults to GL_STATIC_DRAW).
 *
 * @pre glsa::init() must have been called successfully first.
 */
void setBufferData(const Buffer& buffer, const void* data, GLsizeiptr size,
                   GLenum usage = GL_STATIC_DRAW);

/**
 * @brief Upload a std::vector to a buffer object.
 *
 * @tparam T     Element type.
 * @param buffer The target buffer object.
 * @param data   Vector of elements to upload.
 * @param usage  Expected usage pattern (defaults to GL_STATIC_DRAW).
 *
 * @pre glsa::init() must have been called successfully first.
 */
template <typename T>
void setBufferData(const Buffer& buffer, const std::vector<T>& data,
                   GLenum usage = GL_STATIC_DRAW) {
    setBufferData(buffer, data.data(), static_cast<GLsizeiptr>(sizeof(T) * data.size()), usage);
}

/**
 * @brief Upload a std::array to a buffer object.
 *
 * @tparam T     Element type.
 * @tparam N     Number of elements in the array.
 * @param buffer The target buffer object.
 * @param data   Array of elements to upload.
 * @param usage  Expected usage pattern (defaults to GL_STATIC_DRAW).
 *
 * @pre glsa::init() must have been called successfully first.
 */
template <typename T, size_t N>
void setBufferData(const Buffer& buffer, const std::array<T, N>& data,
                   GLenum usage = GL_STATIC_DRAW) {
    setBufferData(buffer, data.data(), static_cast<GLsizeiptr>(sizeof(T) * N), usage);
}

/**
 * @brief Delete a buffer object and release its OpenGL resources.
 *
 * After this call the handle's id is reset to zero.
 *
 * @param buffer The buffer object to destroy. Its id is set to 0 after deletion.
 *
 * @pre glsa::init() must have been called successfully first.
 * @post buffer.id == 0
 */
void deleteBuffer(Buffer& buffer);


/**
 * @brief Configure and enable a vertex attribute pointer on the currently bound VAO.
 *
 * @param index     Attribute location in the vertex shader (`layout(location = index)`).
 * @param attribute Layout description (component count, stride, byte offset, type, normalized).
 *
 * @pre glsa::init() must have been called successfully first, and a VAO and VBO must be bound.
 */
void setVertexAttribPointer(GLuint index, const VertexAttribute& attribute);


/**
 * @brief Compile and link one of the built-in GLSL shader presets.
 *
 * Supported preset names:
 * - "basic": Solid flat color (aPos at location 0, uniform vec4 uColor).
 * - "vertex_color": Per-vertex RGB color (aPos at location 0, aColor at location 1).
 * - "gradient": Vertical two-color blend (aPos at location 0, uniform vec4 uColorBottom, uColorTop).
 * - "pulse": Animated brightness pulse (aPos at location 0, uniform vec4 uColor, float uTime).
 *
 * @param name    Name of the built-in preset to compile.
 * @param version GLSL version directive to inject (defaults to 330).
 *
 * @return A Program handle. id is 0 if the preset name is unknown or compilation failed.
 *
 * @pre glsa::init() must have been called successfully first.
 */
[[nodiscard]] Program shaderPreset(std::string_view name, int version = 330);


/**
 * @brief Draw primitives from indexed array data.
 *
 * @param mode    Primitive type (e.g. GL_POINTS, GL_TRIANGLES).
 * @param count   Number of elements to be rendered.
 * @param type    Type of the values in indices (defaults to GL_UNSIGNED_INT).
 * @param indices Byte offset into the currently bound element array buffer (defaults to nullptr).
 *
 * @pre glsa::init() must have been called successfully first.
 */
void drawElements(GLenum mode, GLsizei count, GLenum type = GL_UNSIGNED_INT,
                  const void* indices = nullptr);


/**
 * @brief Draw a solid 2D axis-aligned rectangle in Normalized Device Coordinates (NDC).
 *
 * Automatically manages an internal shader program, vertex array, and buffer
 * on first call, removing the need for manual VAO/VBO/shader setup for basic 2D quads.
 *
 * @param position Center coordinates (x, y) of the rectangle in NDC [-1.0, 1.0].
 * @param size     Width and height (w, h) of the rectangle in NDC units.
 * @param color    RGBA fill color applied to the rectangle.
 *
 * @pre glsa::init() must have been called successfully first.
 */
void drawRectangle(glm::vec2 position, glm::vec2 size, const glm::vec4& color);

/**
 * @brief Draw a solid 2D circle in Normalized Device Coordinates (NDC).
 *
 * Approximates a circle using a triangle fan with the specified number of perimeter
 * segments. Automatically adjusts horizontal radius using glsa::getAspectRatio()
 * so circles appear round on non-square viewports.
 *
 * @param center   Center coordinates (x, y) of the circle in NDC [-1.0, 1.0].
 * @param radius   Radius of the circle in vertical NDC units.
 * @param color    RGBA fill color applied to the circle.
 * @param segments Number of perimeter segments used to approximate the circle (defaults to 32, minimum 3).
 *
 * @pre glsa::init() must have been called successfully first.
 */
void drawCircle(glm::vec2 center, float radius, const glm::vec4& color, int segments = 32);

} // namespace glsa


// clang-format off
#if defined(GLSA_IMPLEMENTATION) || defined(GLSA_CLANGD_IMPLEMENTATION)

#include "glsa/detail/glsa_internal.h"
#include <glm/gtc/type_ptr.hpp>
// clang-format on

namespace glsa {


namespace internal {

inline bool ensureShapeRenderer() {
    if (g_shape_renderer.initialized) {
        return true;
    }

    g_shape_renderer.program = shaderPreset("basic", 330);
    if (g_shape_renderer.program.id == 0) {
        return false;
    }

    g_shape_renderer.vao = createVertexArray();
    bindVertexArray(g_shape_renderer.vao);

    g_shape_renderer.vbo = createBuffer();
    bindBuffer(g_shape_renderer.vbo);
    setVertexAttribPointer(0, {3, sizeof(glm::vec3), 0});

    g_shape_renderer.initialized = true;
    return true;
}

} // namespace internal


[[nodiscard]] bool init(Extent2D initial_extent) {
    if (initial_extent.width <= 0 || initial_extent.height <= 0) {
        std::fprintf(
            stderr,
            "[GLSA ERROR] Invalid initial extent (%d x %d). Width and height must be > 0.\n",
            initial_extent.width, initial_extent.height);
        return false;
    }

    if (glGetString == nullptr || glGetString(GL_VERSION) == nullptr) {
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

[[nodiscard]] float getAspectRatio() {
    if (!glsa::internal::g_is_initialized) {
        std::fprintf(
            stderr,
            "[GLSA ERROR] Library must be initialized via glsa::init() before calling this "
            "function.\n");
        return 1.0f;
    }

    if (glsa::internal::g_default_extent.height <= 0) {
        return 1.0f;
    }

    return static_cast<float>(glsa::internal::g_default_extent.width) /
           static_cast<float>(glsa::internal::g_default_extent.height);
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


[[nodiscard]] Buffer createBuffer(GLenum target) {
    if (!glsa::internal::g_is_initialized) {
        std::fprintf(
            stderr,
            "[GLSA ERROR] Library must be initialized via glsa::init() before calling this "
            "function.\n");
        return Buffer{0, target};
    }

    Buffer buffer{0, target};
    glGenBuffers(1, &buffer.id);
    return buffer;
}

void bindBuffer(const Buffer& buffer) {
    if (!glsa::internal::g_is_initialized) {
        std::fprintf(
            stderr,
            "[GLSA ERROR] Library must be initialized via glsa::init() before calling this "
            "function.\n");
        return;
    }

    if (buffer.id == 0) {
        std::fprintf(stderr, "[GLSA ERROR] Cannot bind invalid buffer (id == 0).\n");
        return;
    }

    glBindBuffer(buffer.target, buffer.id);
}

void setBufferData(const Buffer& buffer, const void* data, GLsizeiptr size, GLenum usage) {
    if (!glsa::internal::g_is_initialized) {
        std::fprintf(
            stderr,
            "[GLSA ERROR] Library must be initialized via glsa::init() before calling this "
            "function.\n");
        return;
    }

    if (buffer.id == 0) {
        std::fprintf(stderr, "[GLSA ERROR] Cannot upload data to invalid buffer (id == 0).\n");
        return;
    }

    glBindBuffer(buffer.target, buffer.id);
    glBufferData(buffer.target, size, data, usage);
}

void deleteBuffer(Buffer& buffer) {
    if (!glsa::internal::g_is_initialized) {
        std::fprintf(
            stderr,
            "[GLSA ERROR] Library must be initialized via glsa::init() before calling this "
            "function.\n");
        return;
    }

    glDeleteBuffers(1, &buffer.id);
    buffer.id = 0;
}


void setVertexAttribPointer(GLuint index, const VertexAttribute& attribute) {
    if (!glsa::internal::g_is_initialized) {
        std::fprintf(
            stderr,
            "[GLSA ERROR] Library must be initialized via glsa::init() before calling this "
            "function.\n");
        return;
    }

    if (attribute.size < 1 || attribute.size > 4) {
        std::fprintf(stderr,
                     "[GLSA ERROR] Invalid vertex attribute size (%d). Must be between 1 and 4.\n",
                     attribute.size);
        return;
    }

    if (attribute.stride < 0) {
        std::fprintf(stderr, "[GLSA ERROR] Vertex attribute stride cannot be negative.\n");
        return;
    }

    glVertexAttribPointer(index, attribute.size, attribute.type,
                          attribute.normalized ? GL_TRUE : GL_FALSE, attribute.stride,
                          reinterpret_cast<const void*>(attribute.offset)); 
    glEnableVertexAttribArray(index);
}


Program shaderPreset(std::string_view name, int version) {
    std::string header = "#version " + std::to_string(version) + " core\n";

    if (name == "basic") {
        std::string vert = header + R"(
            layout (location = 0) in vec3 aPos;
            void main() {
                gl_Position = vec4(aPos, 1.0);
            }
        )";
        std::string frag = header + R"(
            out vec4 FragColor;
            uniform vec4 uColor;
            void main() {
                FragColor = uColor;
            }
        )";
        return createProgram({vert, frag});
    }

    if (name == "vertex_color") {
        std::string vert = header + R"(
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aColor;
            out vec3 vColor;
            void main() {
                vColor = aColor;
                gl_Position = vec4(aPos, 1.0);
            }
        )";
        std::string frag = header + R"(
            in vec3 vColor;
            out vec4 FragColor;
            void main() {
                FragColor = vec4(vColor, 1.0);
            }
        )";
        return createProgram({vert, frag});
    }

    if (name == "gradient") {
        std::string vert = header + R"(
            layout (location = 0) in vec3 aPos;
            out float vFactor;
            void main() {
                vFactor = clamp(aPos.y * 0.5 + 0.5, 0.0, 1.0);
                gl_Position = vec4(aPos, 1.0);
            }
        )";
        std::string frag = header + R"(
            in float vFactor;
            out vec4 FragColor;
            uniform vec4 uColorBottom;
            uniform vec4 uColorTop;
            void main() {
                FragColor = mix(uColorBottom, uColorTop, vFactor);
            }
        )";
        return createProgram({vert, frag});
    }

    return Program{0};
}

void drawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) {
    if (!internal::g_is_initialized) {
        std::fprintf(stderr, "[GLSA ERROR] glsa::drawElements() called before glsa::init().\n");
        return;
    }
    glDrawElements(mode, count, type, indices);
}



void drawRectangle(glm::vec2 position, glm::vec2 size, const glm::vec4& color) {
    if (!internal::g_is_initialized) {
        std::fprintf(stderr, "[GLSA ERROR] glsa::drawRectangle() called before glsa::init().\n");
        return;
    }

    if (!internal::ensureShapeRenderer()) {
        return;
    }

    const float half_w = size.x * 0.5f;
    const float half_h = size.y * 0.5f;

    const std::array<glm::vec3, 4> vertices = {
        glm::vec3(position.x - half_w, position.y - half_h, 0.0f),
        glm::vec3(position.x + half_w, position.y - half_h, 0.0f),
        glm::vec3(position.x + half_w, position.y + half_h, 0.0f),
        glm::vec3(position.x - half_w, position.y + half_h, 0.0f),
    };

    useProgram(internal::g_shape_renderer.program);
    setUniform(internal::g_shape_renderer.program, "uColor", color);

    bindVertexArray(internal::g_shape_renderer.vao);
    setBufferData(internal::g_shape_renderer.vbo, vertices, GL_DYNAMIC_DRAW);
    drawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void drawCircle(glm::vec2 center, float radius, const glm::vec4& color, int segments) {
    if (!internal::g_is_initialized) {
        std::fprintf(stderr, "[GLSA ERROR] glsa::drawCircle() called before glsa::init().\n");
        return;
    }

    if (segments < 3) {
        std::fprintf(stderr, "[GLSA ERROR] glsa::drawCircle() requires at least 3 segments.\n");
        return;
    }

    if (!internal::ensureShapeRenderer()) {
        return;
    }

    constexpr float TWO_PI = 6.28318530717958647692f;
    const float aspect = getAspectRatio();
    const float radius_x = radius / aspect;

    std::vector<glm::vec3> vertices;
    vertices.reserve(static_cast<std::size_t>(segments) + 2);
    vertices.emplace_back(center.x, center.y, 0.0f);

    for (int i = 0; i <= segments; ++i) {
        const float theta = (static_cast<float>(i) / static_cast<float>(segments)) * TWO_PI;
        const float x = center.x + (radius_x * std::cos(theta));
        const float y = center.y + (radius * std::sin(theta));
        vertices.emplace_back(x, y, 0.0f);
    }

    useProgram(internal::g_shape_renderer.program);
    setUniform(internal::g_shape_renderer.program, "uColor", color);

    bindVertexArray(internal::g_shape_renderer.vao);
    setBufferData(internal::g_shape_renderer.vbo, vertices, GL_DYNAMIC_DRAW);
    drawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(vertices.size()));
}

} // namespace glsa

#endif // GLSA_IMPLEMENTATION || GLSA_CLANGD_IMPLEMENTATION

#undef GLSA_PLATFORM_WINDOWS
#undef GLSA_PLATFORM_MACOS
#undef GLSA_PLATFORM_LINUX
#undef GLSA_MAX_GL_MAJOR
#undef GLSA_MAX_GL_MINOR

#endif // GLSA_GLSA_H