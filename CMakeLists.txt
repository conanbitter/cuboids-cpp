cmake_minimum_required(VERSION 3.16)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(cuboids VERSION 0.1 LANGUAGES C CXX)

set(EXECUTABLE_OUTPUT_PATH ./${CMAKE_BUILD_TYPE})

add_executable(cuboids
    third-party/glad/src/gl.c
    src/main.cpp
    src/vectors.hpp
    src/vectors.cpp
    src/display/shaders.hpp
    src/display/shaders.cpp
    src/display/window.hpp
    src/display/window.cpp
)

find_package(GLFW REQUIRED)

target_include_directories(cuboids
    PUBLIC
        ${GLFW_INCLUDE_DIR}
        third-party/glad/include
)

target_link_directories(cuboids
    PUBLIC
        ${GLFW_LIBRARY}
)

target_link_libraries(cuboids
    glfw3
    opengl32
)