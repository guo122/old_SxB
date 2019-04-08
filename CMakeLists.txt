cmake_minimum_required (VERSION 3.0.2)

project(SxB)

set(CMAKE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")

include(${CMAKE_CURRENT_LIST_DIR}/cmake/Config.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/Macros.cmake)

# enable project folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

add_subdirectory("src")
add_subdirectory("test")
add_subdirectory("example")
