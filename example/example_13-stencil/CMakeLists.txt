
set(PROJECT_NAME example_13-stencil)

set(SRCROOT ${CMAKE_ROOT_DIR}/example/example_13-stencil)

set(DIR_SRCS 
	${SRCROOT}/main.cpp
	${SRCROOT}/stencil.h
	${SRCROOT}/stencil.cpp
	${SRCROOT}/info.h
)

Add_Definitions(-D_HAS_ITERATOR_DEBUGGING=0)

sxb_add_executable(
				${PROJECT_NAME} 
				FOLDER "example" 
				SOURCES ${DIR_SRCS}
)
