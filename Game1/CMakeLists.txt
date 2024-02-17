cmake_minimum_required(VERSION 3.27)
project(Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

# Asset stuff for simplicity
set(DUNGEON_STUFF "assets/private/dungeon-stuff-v2")
set(SPROUT_LANDS "assets/private/sprout-lands")

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
include(cmake/assets.cmake)

add_executable(Game src/main.cpp
        src/Game.cpp
        src/Game.h)

add_compile_definitions(DUNGEON_STUFF="${DUNGEON_STUFF}" SPROUT_LANDS="${SPROUT_LANDS}")
target_link_libraries(Game PRIVATE SDL2::SDL2)
target_link_libraries(Game PRIVATE SDL2_image::SDL2_image-static)
