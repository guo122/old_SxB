cmake_minimum_required (VERSION 3.0.2)

project(SxB)

set(CMAKE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")

include(${CMAKE_CURRENT_LIST_DIR}/cmake/Config.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/Macros.cmake)

# enable project folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

add_subdirectory("src/Example00-HelloWorld")
add_subdirectory("src/Example00-HelloBGFX")
add_subdirectory("src/Example12-lod")
add_subdirectory("src/Example33-pom")

add_subdirectory("tinySFML/src/System")
add_subdirectory("tinySFML/src/Window")

add_subdirectory("tinyBGFX/src/bgfx")
add_subdirectory("tinyBGFX/src/bx")
add_subdirectory("tinyBGFX/src/bimg")

add_subdirectory("src/sxbCommon")

add_subdirectory("test/test_platform")
add_subdirectory("test/test_sfml")


