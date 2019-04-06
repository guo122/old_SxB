
set(PROJECT_NAME test_platform)

set(SRCROOT ${CMAKE_ROOT_DIR}/test/test_platform)

set(DIR_SRCS 
	${SRCROOT}/main.cpp
)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_ROOT_DIR}/bin/x64)
add_executable(${PROJECT_NAME} ${DIR_SRCS})
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "test")

