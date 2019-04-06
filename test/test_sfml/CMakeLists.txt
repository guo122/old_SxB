
set(PROJECT_NAME test_sfml)

set(SRCROOT ${CMAKE_ROOT_DIR}/test/test_sfml)

set(DIR_SRCS 
	${SRCROOT}/main.cpp
)

set(INC_DIR 
	${CMAKE_ROOT_DIR}/tinySFML/include
)
include_directories(${INC_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_ROOT_DIR}/bin/x64)
add_executable(${PROJECT_NAME} ${DIR_SRCS})
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "test")

