
set(TEST_INC_DIR 
	${CMAKE_ROOT_DIR}/3rdparty
	${CMAKE_ROOT_DIR}/include
)
include_directories(${TEST_INC_DIR})

add_subdirectory("test_platform")
add_subdirectory("test_sfml")
add_subdirectory("test_3d")