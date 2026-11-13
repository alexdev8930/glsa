cmake_minimum_required(VERSION 3.21...3.25)
project(GLSA LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY 
        ${CLANG_TIDY_EXE}
        "-checks=bugprone-*,modernize-*,performance-*,readability-*,-modernize-use-trailing-return-type,-readability-magic-numbers,-readability-implicit-bool-conversion,-readability-uppercase-literal-suffix"
        "-warnings-as-errors=*"
        "-header-filter=${CMAKE_CURRENT_SOURCE_DIR}/include/glsa/.*"
    )
endif()

add_subdirectory(external/glad)
add_subdirectory(examples)