
set(SRC_INC_DIR 
	${CMAKE_ROOT_DIR}/3rdparty
	${CMAKE_ROOT_DIR}/include
)

include_directories(${SRC_INC_DIR})

add_subdirectory("bgfx")
add_subdirectory("bimg")
add_subdirectory("bx")
add_subdirectory("SFML/System")
add_subdirectory("SFML/Window")
add_subdirectory("SFML/Main")
add_subdirectory("sxbCommon")
