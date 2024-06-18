cmake_minimum_required(VERSION 3.28)
project(#NAME#)

set(CMAKE_CXX_STANDARD 17)

file(GLOB ENGINE_FILES "src/Engine/*.cpp" "src/Engine/**/*.cpp" "src/Engine/*.h" "src/Engine/**/*.h")

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
        SDL2_image::SDL2_image-static
        SDL2_ttf::SDL2_ttf-static
        EnTT::EnTT
)
