
set(PROJECT_NAME Example00-HelloWorld)

set(DIR_SRCS ${CMAKE_ROOT_DIR}/src/Example00-HelloWorld/main.cpp
			 ${CMAKE_ROOT_DIR}/src/Example00-HelloWorld/logo.h
			)

set(INC_DIR ${CMAKE_ROOT_DIR}/include 
			${CMAKE_ROOT_DIR}/tinyBGFX/include
			${CMAKE_ROOT_DIR}/tinySFML/include
			)

IF (WIN32)
	set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/compat/msvc)
ELSEIF (APPLE)
	set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/compat/osx)
ENDIF()
			
set(LINK_DIR ${CMAKE_ROOT_DIR}/lib/x64/Debug)

set(LINK_LIB 
		tinyBGFX_bgfx
		tinyBGFX_bx 
		tinyBGFX_bimg
		tinySFML_System
		tinySFML_Window
		sxbCommon
	)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})
link_libraries(${LINK_LIB})

Add_Definitions(-D_HAS_ITERATOR_DEBUGGING=0)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_ROOT_DIR}/bin/x64)

add_executable(${PROJECT_NAME} ${DIR_SRCS})

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "example")

