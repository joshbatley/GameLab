cmake_minimum_required(VERSION 3.28)
project(Game_3_Farmer)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)

include(assets/private/gameassets.cmake)
include_directories(${ENTT_INCLUDE_DIRS})

file(GLOB ENGINE src/Engine/*.cpp src/Engine/*.h)
file(GLOB COMPONENTS src/Components/*.cpp src/Components/*.h)

add_executable(Game_3_Farmer src/main.cpp
        ${ENGINE}
        ${COMPONENTS}
        src/Entity.h
        src/Player.h
        src/Player.cpp
)

target_link_libraries(Game_3_Farmer PRIVATE EnTT::EnTT)
target_link_libraries(Game_3_Farmer PRIVATE
        SDL2::SDL2main
        SDL2::SDL2-static
        SDL2_image::SDL2_image-static
        SDL2_ttf::SDL2_ttf-static
)