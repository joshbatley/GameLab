cmake_minimum_required(VERSION 3.15)
project(MetalExample)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/cmake)

file(GLOB cmake_files "${CMAKE_SOURCE_DIR}/cmake/*.cmake")
foreach(cmake_file ${cmake_files})
    include(${cmake_file})
endforeach()

# Find SDL2
find_package(SDL2 CONFIG REQUIRED)

# Include directories for Metal C++ headers
include_directories(${CMAKE_SOURCE_DIR}/metal-cpp)

# Add executable
add_executable(MetalExample main.cpp)

# Link SDL2 and Metal frameworks
target_link_libraries(MetalExample PRIVATE SDL2::SDL2)
