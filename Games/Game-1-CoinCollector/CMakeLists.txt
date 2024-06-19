cmake_minimum_required(VERSION 3.27)
project(Game_1_CoinCollector)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

include(assets/private/gameassets.cmake)

add_executable(Game_1_CoinCollector src/main.cpp
        src/Utils.h
        src/Utils.cpp
        src/Player.cpp
        src/Player.h
        src/Tile.cpp
        src/Tile.h)

target_link_libraries(Game_1_CoinCollector PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static SDL2_ttf::SDL2_ttf-static)

## QQ for Game.app will make a proper build system
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(Game_1_CoinCollector PROPERTIES MACOSX_BUNDLE TRUE)
    file(COPY ${CMAKE_BINARY_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/Game.app/Contents/Resources/)
endif ()