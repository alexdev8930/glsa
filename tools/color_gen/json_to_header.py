"""
json_to_header.py

Converts RGB color definitions from lots_of_colors.json into C++ inline constexpr
glm::vec4 constants inside include/glsa/glsa_colors.h.

Copyright (c) 2026 AlexDev
License: MIT
"""

import json
import re
from pathlib import Path

json_path = "tools/color_gen/lots_of_colors.json"
out_path = "include/glsa/glsa_colors.h"

HEADER_TOP = """/**
 * @file glsa_colors.h
 * @brief Predefined vec4 glm color constants for GLSA.
 *
 * @note Auto-generated file. Do not edit manually.
 * @source tools/color_gen/lots_of_colors.json
 * @script tools/color_gen/json_to_header.py
 *
 * @copyright Copyright (c) 2026 AlexDev
 * @license MIT
 */

// clang-format off
#ifndef GLSA_GLSA_COLORS_H
#define GLSA_GLSA_COLORS_H

#include <glm/vec4.hpp>

namespace glsa {

[[nodiscard]] constexpr glm::vec4 overrideAlpha(const glm::vec4& color, float alpha) noexcept {
    return { color.r, color.g, color.b, alpha };
}

namespace colors {
"""

HEADER_BOTTOM = """} // namespace colors

} // namespace glsa

#endif // GLSA_GLSA_COLORS_H
// clang-format on
"""

keywords = {
    "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
    "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t",
    "class", "compl", "concept", "const", "consteval", "constexpr", "constinit",
    "const_cast", "continue", "co_await", "co_return", "co_yield", "decltype",
    "default", "delete", "do", "double", "dynamic_cast", "else", "enum",
    "explicit", "export", "extern", "false", "float", "for", "friend", "goto",
    "if", "inline", "int", "long", "mutable", "namespace", "new", "noexcept",
    "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private",
    "protected", "public", "register", "reinterpret_cast", "requires", "return",
    "short", "signed", "sizeof", "static", "static_assert", "static_cast",
    "struct", "switch", "template", "this", "thread_local", "throw", "true",
    "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
    "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
}

def make_valid_name(name):
    name = re.sub(r"[^A-Za-z0-9_]", "_", name).upper()
    name = re.sub(r"_+", "_", name).strip("_")
    if not name or name[0].isdigit():
        name = "_" + name
    if name.lower() in keywords:
        name += "_"
    return name

with open(json_path, "r", encoding="utf-8") as f:
    colors = json.load(f)

used_names = set()

with open(out_path, "w", encoding="utf-8") as out:
    out.write(HEADER_TOP)

    for key, val in colors.items():
        name = make_valid_name(val.get("name", key))
        orig = name
        num = 2
        while name in used_names:
            name = f"{orig}_{num}"
            num += 1
        used_names.add(name)

        r_int = val["red"]
        g_int = val["green"]
        b_int = val["blue"]
        r = r_int / 255.0
        g = g_int / 255.0
        b = b_int / 255.0
        hex_str = f"#{r_int:02X}{g_int:02X}{b_int:02X}"

        out.write(f"    inline constexpr glm::vec4 {name}({r:.6f}f, {g:.6f}f, {b:.6f}f, 1.0f); /**< {hex_str} | RGB({r_int}, {g_int}, {b_int}) */\n")

    out.write(HEADER_BOTTOM)

print(f"Wrote {len(used_names)} colors to {out_path}")
