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

#include <string>
#include "glsa/glsa_types.h"

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


} // namespace glsa


// clang-format off
#if defined(GLSA_IMPLEMENTATION) || defined(GLSA_CLANGD_IMPLEMENTATION)

#include <GLFW/glfw3.h>

namespace glsa {

    
inline Extent2D g_default_extent{0, 0};


[[nodiscard]] bool init(Extent2D initial_extent) {
    if (initial_extent.width <= 0 || initial_extent.height <= 0) {
        return false;
    }

    if (glfwGetCurrentContext() == nullptr) {
        return false;
    }

    g_default_extent = initial_extent;
    return true;
}


Extent2D getDefaultExtent() {
    return g_default_extent;
}


} // namespace glsa

#endif // GLSA_IMPLEMENTATION || GLSA_CLANGD_IMPLEMENTATION
// clang-format on

#undef GLSA_PLATFORM_WINDOWS
#undef GLSA_PLATFORM_MACOS
#undef GLSA_PLATFORM_LINUX
#undef GLSA_MAX_GL_MAJOR
#undef GLSA_MAX_GL_MINOR

#endif // GLSA_GLSA_H