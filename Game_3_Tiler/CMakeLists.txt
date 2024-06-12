cmake_minimum_required(VERSION 3.28)
project(Game_3_Tiler)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_library(FastNoise
        NAMES FastNoise
        HINTS "lib/FastNoise.h")

include(assets/private/gameassets.cmake)
include_directories(lib)

file(GLOB ENGINE src/Engine/*.cpp src/Engine/*.h)
file(GLOB COMPONENTS src/Components/*.cpp src/Components/*.h)
file(GLOB SYSTEMS src/System/*.cpp src/System/*.h)
file(GLOB UTILS src/Utils/*.cpp src/Utils/*.h)

add_executable(Game_3_Tiler src/main.cpp
        ${ENGINE}
        ${COMPONENTS}
        ${SYSTEMS}
        ${UTILS}
        src/App.cpp
        src/App.h
        src/Dispatcher.h
        src/AssetManager.cpp
        src/AssetManager.h
        src/Events.h
)

target_link_libraries(Game_3_Tiler PRIVATE
        SDL2::SDL2main
        SDL2::SDL2-static
        SDL2_image::SDL2_image-static
        SDL2_ttf::SDL2_ttf-static
        EnTT::EnTT
)