cmake_minimum_required(VERSION 3.27)
project(Game1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

find_package(SDL2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(Game1 main.cpp)

target_link_libraries(Game1 PRIVATE SDL2::SDL2)
target_link_libraries(Game1 PRIVATE imgui::imgui)
