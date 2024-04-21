cmake_minimum_required(VERSION 3.10)
project(BasicRender)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(
    include/
    lib/glad/include/
    lib/glfw/include/
    lib/glm/
)

add_executable(
    ${PROJECT_NAME}
    src/Main.cpp
    lib/glad/src/glad.c
)

target_link_options(
    ${PROJECT_NAME}
    PRIVATE "/NODEFAULTLIB:MSVCRT"
)

target_link_libraries(
    ${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/lib/glfw/glfw3.lib
)
