/**
 * @file glsa_internal.h
 * @brief Internal runtime state and private helpers for GLSA.
 */

#pragma once

#include "glsa/glsa_types.h"

namespace glsa::internal {

// Tracks whether glsa::init() has succeeded on the active context.
inline bool g_is_initialized = false;

// Cached render bounds configured during glsa::init().
inline Extent2D g_default_extent{0, 0};

} // namespace glsa::internal
