cmake_minimum_required(VERSION 3.28)
project(#NAME#)

set(CMAKE_CXX_STANDARD 17)

include_directories(Engine)
file(GLOB ENGINE_FILES Engine/**/*.cpp)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)

include(assets/private/gameassets.cmake)

add_executable(#NAME#
        src/main.cpp
        ${ENGINE_FILES}
)

target_link_libraries(#NAME# PRIVATE
        SDL2::SDL2main
        SDL2::SDL2-static
        SDL2_image::SDL2_image-static
        SDL2_ttf::SDL2_ttf-static
        EnTT::EnTT
)
