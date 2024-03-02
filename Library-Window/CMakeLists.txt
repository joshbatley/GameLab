cmake_minimum_required(VERSION 3.27)
project(Library_Window)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

add_library(Library_Window STATIC Window.cpp)

target_link_libraries(Library_Window PRIVATE SDL2::SDL2)
target_link_libraries(Library_Window PRIVATE SDL2_ttf::SDL2_ttf-static)
target_link_libraries(Library_Window PRIVATE SDL2_image::SDL2_image-static)
