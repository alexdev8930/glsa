# Dependencies
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Example executables
add_executable(glsa_demo example.cpp)

target_include_directories(glsa_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(glsa_demo PRIVATE
    glad
    glfw
    glm::glm
)

add_executable(glsa_basic_shapes basic_shapes.cpp)

target_include_directories(glsa_basic_shapes PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(glsa_basic_shapes PRIVATE
    glad
    glfw
    glm::glm
)

add_custom_target(run-examples
    COMMAND "$<TARGET_FILE:glsa_demo>"
    COMMAND "$<TARGET_FILE:glsa_basic_shapes>"
    DEPENDS glsa_demo glsa_basic_shapes
    WORKING_DIRECTORY "$<TARGET_FILE_DIR:glsa_demo>"
    USES_TERMINAL
    VERBATIM
)
