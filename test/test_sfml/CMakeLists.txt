
set(PROJECT_NAME test_sfml)

set(SRCROOT ${CMAKE_ROOT_DIR}/test/test_sfml)

set(DIR_SRCS 
	${SRCROOT}/main.cpp
)

set(INC_DIR 
	${CMAKE_ROOT_DIR}/tinySFML/include
)
include_directories(${INC_DIR})

sxb_add_executable(
				${PROJECT_NAME} 
				FOLDER "test" 
				SOURCES ${DIR_SRCS}
)