cmake_minimum_required(VERSION 3.28)
project(Game_3_Tiler)

set(CMAKE_CXX_STANDARD 17)

#add_subdirectory(src/Engine)

file(GLOB_RECURSE ENGINE_SOURCES "src/Engine/*.cpp" "src/Engine/**/*.cpp")
file(GLOB_RECURSE ENGINE_HEADERS "src/Engine/*.h" "src/Engine/**/*.h")
add_library(Engine ${ENGINE_SOURCES} ${ENGINE_HEADERS}
        src/Engine/Alias.h)

target_link_libraries(Engine PRIVATE
        SDL2::SDL2main
        SDL2::SDL2-static
        SDL2_image::SDL2_image-static
        SDL2_ttf::SDL2_ttf-static
        EnTT::EnTT
)

file(GLOB COMPONENTS src/Components/*.cpp src/Components/*.h)
file(GLOB SYSTEMS src/System/*.cpp src/System/*.h)
file(GLOB UTILS src/Utils/*.cpp src/Utils/*.h)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)

include(assets/private/gameassets.cmake)
include_directories(lib)

add_executable(Game_3_Tiler src/main.cpp
        ${COMPONENTS}
        ${SYSTEMS}
        ${UTILS}
        src/Events.h
        src/Utils/TileUtils.h
)


target_link_libraries(Game_3_Tiler PRIVATE
        Engine
        SDL2::SDL2main
        SDL2_image::SDL2_image-static
        SDL2_ttf::SDL2_ttf-static
        EnTT::EnTT
)
