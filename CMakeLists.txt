cmake_minimum_required(VERSION 3.20)
project(gravity_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(gravity_lab
    src/main.cpp
    src/physics.cpp
    src/render.cpp
)

target_include_directories(gravity_lab PRIVATE includes)

target_link_libraries(gravity_lab PRIVATE
    OpenGL::GL
    glfw
)
