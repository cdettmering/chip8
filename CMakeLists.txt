cmake_minimum_required (VERSION 2.8)
project (chip8)

find_package (Glog REQUIRED)
find_package (SDL2 REQUIRED)

set (chip8 _VERSION_MAJOR 0)
set (chip8 _VERSION_MINOR 1)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

add_subdirectory (src)
