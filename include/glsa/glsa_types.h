/**
 * @file glsa_types.h
 * @brief Core data structures and resource handles for GLSA.
 *
 * @details
 * Defines lightweight value types, configuration extents, and opaque OpenGL
 * resource handles used across the GLSA public API.
 *
 * @copyright Copyright (c) 2026 AlexDev
 * @license MIT
 */

#ifndef GLSA_GLSA_TYPES_H
#define GLSA_GLSA_TYPES_H

#include <string_view>

namespace glsa {

/**
 * @brief Simple configuration structure for uniform dimensions.
 */
struct Extent2D {
    int width;  /**< Width component, in pixels or units. Must be > 0. */
    int height; /**< Height component, in pixels or units. Must be > 0. */
};
 

/**
 * @brief Opaque handle to a linked OpenGL shader program.
 *
 * The id is zero when the handle is invalid (e.g. program creation failed).
 */
struct Program {
    unsigned int id = 0;
};


/**
 * @brief Container holding null-terminated GLSL shader source strings.
 * Prevents positional parameter swapping bugs during program creation.
 */
struct ShaderSource {
    std::string_view vertex;   /**< GLSL vertex shader source code text. */
    std::string_view fragment; /**< GLSL fragment shader source code text. */
};

/**
 * @brief Opaque handle to a vertex array object.
 *
 * The id is zero when the handle is invalid.
 */
struct VertexArray {
    unsigned int id = 0;
};

/**
 * @brief Opaque handle to a GPU buffer object (e.g. VBO, EBO).
 *
 * The id is zero when the handle is invalid.
 */
struct Buffer {
    unsigned int id = 0;     /**< OpenGL buffer object name. */
    unsigned int target = 0; /**< OpenGL binding target (e.g. GL_ARRAY_BUFFER). */
};

/**
 * @brief Layout description for a single vertex attribute in a VAO.
 */
struct VertexAttribute {
    int size = 0;               /**< Number of components per vertex (1, 2, 3, or 4). */
    int stride = 0;             /**< Byte offset between consecutive vertices. */
    std::size_t offset = 0;     /**< Byte offset of the first component in the buffer. */
    unsigned int type = 0x1406; /**< Component data type (defaults to GL_FLOAT). */
    bool normalized = false;    /**< Whether fixed-point values should be normalized. */
};

} // namespace glsa

#endif // GLSA_GLSA_TYPES_H