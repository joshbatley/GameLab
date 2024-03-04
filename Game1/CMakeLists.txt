cmake_minimum_required(VERSION 3.27)
project(Game)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
include(assets/private/gameassets.cmake)

add_executable(Game src/main.cpp
        src/Utils.h
        src/Utils.cpp
        src/Player.cpp
        src/Player.h
        src/Tile.cpp
        src/Tile.h)

target_link_libraries(Game PRIVATE SDL2::SDL2)
target_link_libraries(Game PRIVATE SDL2_ttf::SDL2_ttf-static)
target_link_libraries(Game PRIVATE SDL2_image::SDL2_image-static)

## QQ for Game.app will make a proper build system
set_target_properties(Game PROPERTIES MACOSX_BUNDLE TRUE)
file(COPY ${CMAKE_BINARY_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/Game.app/Contents/Resources/)
