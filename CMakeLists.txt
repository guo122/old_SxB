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

############3

macro(sfml_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

if(SXB_OS_MACOS)
	    sfml_set_option(SFML_BUILD_FRAMEWORKS FALSE BOOL "TRUE to build SFML as frameworks libraries (release only), FALSE to build according to BUILD_SHARED_LIBS")

    # add an option to let the user specify a custom directory for external frameworks installation
    sfml_set_option(SFML_DEPENDENCIES_INSTALL_PREFIX "/Library/Frameworks" PATH "External frameworks (FLAC, Freetype, Vorbis, ...) installation directory")

    # add an option to automatically install Xcode templates
    sfml_set_option(SFML_INSTALL_XCODE_TEMPLATES FALSE BOOL "TRUE to automatically install the Xcode templates, FALSE to do nothing about it. The templates are compatible with Xcode 4 and 5.")
endif()

sfml_set_option(SFML_OPENGL_ES ${OPENGL_ES} BOOL "TRUE to use an OpenGL ES implementation, FALSE to use a desktop OpenGL implementation")

# define SFML_OPENGL_ES if needed
if(SFML_OPENGL_ES)
    add_definitions(-DSFML_OPENGL_ES)
    add_definitions(-DGL_GLEXT_PROTOTYPES)
endif()
#############

add_subdirectory("src")
add_subdirectory("example")

#if(SXB_OS_IOS)
	#add_subdirectory("ios")
	#endif()

if(SXB_TEST)
	add_subdirectory("test")
endif()

set(CPACK_PACKAGE_DIRECTORY ${CMAKE_ROOT_DIR}/pack)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_ROOT_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
set(PROJECT_VERSION_FULL ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

set(CPACK_SOURCE_IGNORE_FILES
        ${CMAKE_ROOT_DIR}/bin
        ${CMAKE_ROOT_DIR}/lib
        ${CMAKE_ROOT_DIR}/build-win
        ${CMAKE_ROOT_DIR}/build-ios
        ${CMAKE_ROOT_DIR}/build-macos
        ${CMAKE_ROOT_DIR}/pack
        ${CMAKE_ROOT_DIR}/.DS_Store
        ${CMAKE_ROOT_DIR}/.vs
        ${CMAKE_ROOT_DIR}/.git
        ${CMAKE_ROOT_DIR}/.gitignore
)

set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME sxb-${PROJECT_VERSION_FULL})

include(CPack)
