
set(PROJECT_NAME test_3d)

set(SRCROOT ${CMAKE_ROOT_DIR}/test/test_3d)

set(DIR_SRCS 
	${SRCROOT}/main.cpp
	${SRCROOT}/cube.h
	${SRCROOT}/cube.cpp
)

IF (SXB_OS_WINDOWS)
	set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/include/bx/compat/msvc)
ELSEIF (SXB_OS_MACOS)
	set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/include/bx/compat/osx)
ENDIF()

set(LINK_LIBS 
	bgfx
	bx
	bimg
	sfml-system
	sfml-window
	sxbCommon
)

include_directories(${INC_DIR})
link_libraries(${LINK_LIBS})

Add_Definitions(-D_HAS_ITERATOR_DEBUGGING=0)

sxb_add_executable(
				${PROJECT_NAME} 
				FOLDER "test" 
				SOURCES ${DIR_SRCS}
)