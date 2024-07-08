cmake_minimum_required(VERSION 3.28)
project(Tool-4-TileMapper)

set(CMAKE_CXX_STANDARD 20)

include(assets/private/gameassets.cmake)
add_subdirectory(Engine)

add_executable(Tool-4-TileMapper src/main.cpp
        src/Panel.cpp
        src/Panel.h
        src/Camera/Camera.cpp
        src/Camera/Camera.h
        src/File.h
)

target_link_libraries(Tool-4-TileMapper PRIVATE Engine)
