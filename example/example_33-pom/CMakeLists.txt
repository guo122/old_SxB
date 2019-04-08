
set(PROJECT_NAME example_33-pom)

set(SRCROOT ${CMAKE_ROOT_DIR}/example/example_33-pom)

set(DIR_SRCS 
	${SRCROOT}/main.cpp
)

Add_Definitions(-D_HAS_ITERATOR_DEBUGGING=0)

sxb_add_executable(
				${PROJECT_NAME} 
				FOLDER "example" 
				SOURCES ${DIR_SRCS}
)