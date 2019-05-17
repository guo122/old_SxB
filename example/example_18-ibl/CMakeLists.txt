
set(PROJECT_NAME example_18-ibl)

set(SRCROOT ${CMAKE_ROOT_DIR}/example/example_18-ibl)

set(DIR_SRCS 
	${SRCROOT}/main.cpp
	${SRCROOT}/ibl.h
	${SRCROOT}/ibl.cpp
)

Add_Definitions(-D_HAS_ITERATOR_DEBUGGING=0)

sxb_add_executable(
				${PROJECT_NAME} 
				FOLDER "example" 
				SOURCES ${DIR_SRCS}
)
