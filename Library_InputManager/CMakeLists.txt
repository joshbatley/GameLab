cmake_minimum_required(VERSION 3.27)
project(Library_InputManager)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)

add_library(Library_InputManager STATIC InputManager.cpp)

target_link_libraries(Library_InputManager PRIVATE SDL2::SDL2)
