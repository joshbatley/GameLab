cmake_minimum_required(VERSION 3.27)
project(Library_InputManger)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)

add_library(Library_InputManger STATIC InputManager.cpp)

target_link_libraries(Library_InputManger PRIVATE SDL2::SDL2)
