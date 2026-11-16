/**
 * @file glsa_internal.h
 * @brief Internal runtime state and private helpers for GLSA.
 *
 * @copyright Copyright (c) 2026 AlexDev
 * @license MIT
 */

#pragma once

#include "glsa/glsa_types.h"

namespace glsa::internal {

// Tracks whether glsa::init() has succeeded on the active context.
inline bool g_is_initialized = false;

// Cached render bounds configured during glsa::init().
inline Extent2D g_default_extent{0, 0};

// Cached GPU resources used exclusively by immediate shape helpers (drawRectangle, drawCircle).
struct ShapeRendererState {
    Program program{};
    VertexArray vao{};
    Buffer vbo{};
    bool initialized = false;
};

// Shared state instance for 2D immediate shape rendering.
inline ShapeRendererState g_shape_renderer{};

} // namespace glsa::internal
