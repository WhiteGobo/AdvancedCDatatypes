cmake_minimum_required(VERSION 3.25)
set(CMAKE_C_FLAGS "-g") #enable lines in memtest

project(AdvancedCDatatypes VERSION 0.1.0 LANGUAGES C)

include(packages.cmake)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
