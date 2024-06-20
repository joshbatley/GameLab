cmake_minimum_required(VERSION 3.29)
project(Engine)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)

file(GLOB COMPONENTS src/Components/*.cpp src/Components/*.h)
file(GLOB SYSTEMS src/Systems/*.cpp src/Systems/*.h)
file(GLOB CORE src/Core/*.cpp src/Core/*.h)

add_library(Engine STATIC
        src/Engine.h
        ${COMPONENTS}
        ${SYSTEMS}
        ${CORE}
)

target_link_libraries(Engine PRIVATE
        SDL2::SDL2main
        SDL2::SDL2-static
        SDL2_image::SDL2_image-static
        SDL2_ttf::SDL2_ttf-static
        EnTT::EnTT
)

target_include_directories(Engine PUBLIC ${SDL2_INCLUDE_DIRS} src)