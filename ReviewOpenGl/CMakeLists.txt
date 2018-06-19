cmake_minimum_required(VERSION 3.10)
project(ReviewOpenGl)

set(CMAKE_CXX_STANDARD 11)

set( ROOT ${PROJECT_SOURCE_DIR})
include_directories(${ROOT}/Include)
#link_directories(${ROOT}/Lib/X86)
link_directories(${ROOT}/Lib/X64)

add_subdirectory(1_CreatWindow)
add_subdirectory(2_CreatTriangle)
add_subdirectory(3_GLSL)
add_subdirectory(4_Texture_Transfrom)
add_subdirectory(5_Camera)
add_subdirectory(6_LightMaterial)
add_subdirectory(7_LightCast)
add_subdirectory(8_StencilTest)