cmake_minimum_required(VERSION 3.28)
project(Tool-4-TileMapper)

set(CMAKE_CXX_STANDARD 17)

include(assets/private/gameassets.cmake)
add_subdirectory(Engine)

add_executable(Tool-4-TileMapper src/main.cpp)

target_link_libraries(Tool-4-TileMapper PRIVATE Engine)
