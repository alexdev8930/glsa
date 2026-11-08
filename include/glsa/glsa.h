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
 * - GLAD
 * - GLM
 *
 * @copyright Copyright (c) 2026 AlexDev
 * @license MIT
 */

#ifndef GLSA_GLSA_H
#define GLSA_GLSA_H

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
 * @brief Initializes the GLSA runtime context and loads OpenGL function pointers
 *
 * @param width The initial width of the rendering area or window viewport
 * @param height The initial height of the rendering area or window viewport
 *
 * @pre A valid window and OpenGL context (via GLFW) MUST be initialized
 *      and made current on the active thread before calling this function
 *
 * @return true If the graphics loader bound successfully and the system driver
 *              context satisfies your core major/minor version limits.
 * @return false If GLAD fails to parse function addresses or if the driver version 
 *               falls below your minimum threshold floor.
 */
bool init(int width, int height);

} // namespace glsa

#ifdef GLSA_IMPLEMENTATION

    // Implementation goes here

#endif // GLSA_IMPLEMENTATION

#undef GLSA_PLATFORM_WINDOWS
#undef GLSA_PLATFORM_MACOS
#undef GLSA_PLATFORM_LINUX
#undef GLSA_MAX_GL_MAJOR
#undef GLSA_MAX_GL_MINOR

#endif // GLSA_GLSA_H