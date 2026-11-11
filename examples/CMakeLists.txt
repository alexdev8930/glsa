# Dependencies
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Example executable
add_executable(glsa_demo example.cpp)

target_include_directories(glsa_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(glsa_demo PRIVATE
    glad
    glfw
    glm::glm
)

add_custom_target(run-examples
    COMMAND "$<TARGET_FILE:glsa_demo>"
    DEPENDS glsa_demo
    WORKING_DIRECTORY "$<TARGET_FILE_DIR:glsa_demo>"
    USES_TERMINAL
    VERBATIM
)
