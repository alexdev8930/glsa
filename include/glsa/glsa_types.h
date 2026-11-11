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

} // namespace glsa

#endif // GLSA_GLSA_TYPES_H