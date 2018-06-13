cmake_minimum_required(VERSION 3.10)
project(ReviewOpenGl)

set(CMAKE_CXX_STANDARD 11)

set( ROOT ${PROJECT_SOURCE_DIR})
include_directories(${ROOT}/Include)
link_directories(${ROOT}/Lib/X86)

add_subdirectory(1_CreatWindow)
add_subdirectory(2_CreatTriangle)
add_subdirectory(3_GLSL)