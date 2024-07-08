cmake_minimum_required(VERSION 3.29)
project(Engine)

set(CMAKE_CXX_STANDARD 20)

set(VCPKG_MANIFEST_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(VCPKG_MANIFEST_INSTALL ON)
set(VCPKG_MANIFEST_MODE ON)
set(VCPKG_APPLOCAL_DEPS ON)
set(VCPKG_PREFER_SYSTEM_LIBS OFF)

include("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

set(ENABLE_IMGUI FALSE)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

file(GLOB COMPONENTS src/Components/*.cpp src/Components/*.h)
file(GLOB SYSTEMS src/Systems/*.cpp src/Systems/*.h)
file(GLOB CORE src/Core/*.cpp src/Core/*.h)
file(GLOB UTILS src/Utils/*.cpp src/Utils/*.h)

add_library(Engine STATIC
        src/Engine.h
        ${COMPONENTS}
        ${SYSTEMS}
        ${CORE}
        ${UTILS}
)

target_link_libraries(Engine PRIVATE
        SDL2::SDL2main
        SDL2::SDL2-static
        SDL2_image::SDL2_image-static
        SDL2_ttf::SDL2_ttf-static
        EnTT::EnTT
        glm::glm
        imgui::imgui
)

target_include_directories(Engine PUBLIC ${SDL2_INCLUDE_DIRS} src)

add_compile_definitions(
        ENABLE_IMGUI="${ENABLE_IMGUI}"
)