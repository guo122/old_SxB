
set(EXAMPLE_INC_DIR 
	${CMAKE_ROOT_DIR}/3rdparty
	${CMAKE_ROOT_DIR}/include
)

IF (SXB_OS_WINDOWS)
	set(EXAMPLE_INC_DIR ${EXAMPLE_INC_DIR} ${CMAKE_ROOT_DIR}/include/bx/compat/msvc)
ELSEIF (SXB_OS_MACOS)
	set(EXAMPLE_INC_DIR ${EXAMPLE_INC_DIR} ${CMAKE_ROOT_DIR}/include/bx/compat/osx)
ENDIF()

set(EXAMPLE_LINK_LIBS 
	bgfx
	bx
	bimg
	sfml-system
	sfml-window
	sxbCommon
)

include_directories(${EXAMPLE_INC_DIR})
link_libraries(${EXAMPLE_LINK_LIBS})

add_subdirectory("example_00-HelloBGFX")
add_subdirectory("example_00-HelloWorld")
add_subdirectory("example_12-lod")
add_subdirectory("example_13-stencil")
add_subdirectory("example_33-pom")