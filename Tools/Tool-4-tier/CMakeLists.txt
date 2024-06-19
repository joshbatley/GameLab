cmake_minimum_required(VERSION 3.29)
project(tier)

set(CMAKE_CXX_STANDARD 20)

#include_directories(Lib/Engine)
#add_subdirectory(Lib/Engin)

include(assets/private/gameassets.cmake)
include_directories(Lib)
add_subdirectory(Engine)

file(GLOB COMPONENTS src/Components/*.cpp src/Components/*.h)
file(GLOB SYSTEMS src/System/*.cpp src/System/*.h)
file(GLOB UTILS src/Utils/*.cpp src/Utils/*.h)

add_executable(tier
        src/main.cpp
        ${COMPONENTS}
        ${SYSTEMS}
        ${UTILS}
        src/Events.h
)
target_link_libraries(tier PRIVATE Engine)
