cmake_minimum_required(VERSION 3.0.0)
project(OpenGL VERSION 0.1.0)


set(SOURCES 
src/glad.c 
src/main.cpp
src/stb_image.cpp)


include_directories(include)
link_directories(lib)
add_executable(OpenGL ${SOURCES})
target_link_libraries(OpenGL libglfw3.a)