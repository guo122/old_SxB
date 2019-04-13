
set(PROJECT_NAME eg_ios_00-HelloBGFX)

set(SRCROOT ${CMAKE_ROOT_DIR}/example/eg_ios_00-HelloBGFX)

set(DIR_SRCS 
	${SRCROOT}/main.mm
	${SRCROOT}/cube.h
	${SRCROOT}/cube.cpp
)

Add_Definitions(-D_HAS_ITERATOR_DEBUGGING=0)

sxb_add_executable(
				${PROJECT_NAME} 
				FOLDER "example" 
				SOURCES ${DIR_SRCS}
)

