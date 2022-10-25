cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME GL_test)
project(${PROJECT_NAME})

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Configure.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Compiler.cmake")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw")
include_directories("${CMAKE_SOURCE_DIR}/3rdparty/glfw/include")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glad")
include_directories("${CMAKE_SOURCE_DIR}/3rdparty/glad/include")

add_subdirectory(src)




