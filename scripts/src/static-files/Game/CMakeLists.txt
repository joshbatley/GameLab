cmake_minimum_required(VERSION 3.28)
project(#NAME#)

set(CMAKE_CXX_STANDARD 17)

include(assets/private/gameassets.cmake)
add_subdirectory(Engine)

add_executable(#NAME# src/main.cpp)

target_link_libraries(#NAME# PRIVATE Engine)
