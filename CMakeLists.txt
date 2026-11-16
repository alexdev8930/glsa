cmake_minimum_required(VERSION 3.21...3.25)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(GLSA_IS_TOP_LEVEL ON)
else()
    set(GLSA_IS_TOP_LEVEL OFF)
endif()

option(GLSA_BUILD_EXAMPLES "Build GLSA example applications" ${GLSA_IS_TOP_LEVEL})
if(GLSA_BUILD_EXAMPLES)
    list(APPEND VCPKG_MANIFEST_FEATURES "examples")
endif()

project(GLSA LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()

add_subdirectory(external/glad)

if(GLSA_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
