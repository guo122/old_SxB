
set(PROJECT_NAME example_12-lod)

set(SRCROOT ${CMAKE_ROOT_DIR}/example/example_12-lod)

set(DIR_SRCS 
	${SRCROOT}/main.cpp
	${SRCROOT}/lod.h
	${SRCROOT}/lod.cpp
)
			
Add_Definitions(-D_HAS_ITERATOR_DEBUGGING=0)

sxb_add_executable(
				${PROJECT_NAME} 
				FOLDER "example" 
				SOURCES ${DIR_SRCS}
)