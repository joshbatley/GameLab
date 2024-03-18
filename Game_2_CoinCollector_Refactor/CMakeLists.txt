cmake_minimum_required(VERSION 3.27)
project(Game_2_CoinCollector_Refactor)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

include(assets/private/gameassets.cmake)

add_executable(Game_2_CoinCollector_Refactor src/main.cpp
        src/InputManager.h
        src/InputManager.cpp
        src/WindowManager.cpp
        src/WindowManager.h
        src/Player.cpp
        src/Player.h
        src/Player.h
        src/Tile.cpp
        src/Tile.h
        src/Renderer.cpp
        src/Renderer.h
)

target_link_libraries(Game_2_CoinCollector_Refactor PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static SDL2_ttf::SDL2_ttf-static)

