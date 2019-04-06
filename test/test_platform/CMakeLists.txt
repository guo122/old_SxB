
set(PROJECT_NAME test_platform)

set(SRCROOT ${CMAKE_ROOT_DIR}/test/test_platform)

set(DIR_SRCS 
	${SRCROOT}/main.cpp
)

sxb_add_executable(
				${PROJECT_NAME} 
				FOLDER "test" 
				SOURCES ${DIR_SRCS}
)