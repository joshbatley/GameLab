cmake_minimum_required(VERSION 3.28)
project(#NAME#)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE ENGINE_SOURCES "src/Engine/*.cpp" "src/Engine/**/*.cpp")
file(GLOB_RECURSE ENGINE_HEADERS "src/Engine/*.h" "src/Engine/**/*.h")
add_library(Engine ${ENGINE_SOURCES} ${ENGINE_HEADERS})

target_link_libraries(Engine PRIVATE
        SDL2::SDL2main
        SDL2::SDL2-static
        SDL2_image::SDL2_image-static
        SDL2_ttf::SDL2_ttf-static
        EnTT::EnTT
)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)

include(assets/private/gameassets.cmake)

add_executable(#NAME# src/main.cpp)

target_link_libraries(#NAME# PRIVATE
        Engine
        SDL2::SDL2main
        SDL2_image::SDL2_image-static
        SDL2_ttf::SDL2_ttf-static
        EnTT::EnTT
)
