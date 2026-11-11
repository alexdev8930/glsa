cmake_minimum_required(VERSION 3.21)
project(external_glad LANGUAGES C)

add_library(glad STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/gl.c")

target_include_directories(glad SYSTEM PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

set_target_properties(glad PROPERTIES 
    C_CLANG_TIDY ""
    CXX_CLANG_TIDY ""
)
