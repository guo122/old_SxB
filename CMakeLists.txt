cmake_minimum_required (VERSION 3.7.2)

project(SxB)

set(CMAKE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")

# enable project folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

add_subdirectory("src/Example01-HelloWorld")
add_subdirectory("src/Example02-HelloBGFX")
add_subdirectory("src/ExampleTest")
