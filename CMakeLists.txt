cmake_minimum_required (VERSION 3.0.2)

project(SxB)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 1)

set(CMAKE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")

include(${CMAKE_ROOT_DIR}/cmake/Config.cmake)
include(${CMAKE_ROOT_DIR}/cmake/Macros.cmake)

# enable project folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

add_subdirectory("src")
add_subdirectory("test")
add_subdirectory("example")

set(CPACK_PACKAGE_DIRECTORY ${CMAKE_ROOT_DIR}/pack)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_ROOT_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
set(PROJECT_VERSION_FULL ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

set(CPACK_SOURCE_IGNORE_FILES
        ${CMAKE_ROOT_DIR}/bin
        ${CMAKE_ROOT_DIR}/lib
        ${CMAKE_ROOT_DIR}/build
        ${CMAKE_ROOT_DIR}/pack
        ${CMAKE_ROOT_DIR}/.DS_Store
        ${CMAKE_ROOT_DIR}/.vs
        ${CMAKE_ROOT_DIR}/.git
        ${CMAKE_ROOT_DIR}/.gitignore
)

set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME sxb-${PROJECT_VERSION_FULL})

include(CPack)