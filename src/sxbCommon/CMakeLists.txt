
set(PROJECT_NAME sxbCommon)

set(DIR_SRCS ${CMAKE_ROOT_DIR}/include/sxbTop/defines.h
			 ${CMAKE_ROOT_DIR}/include/sxbCommon/utils.h
			 ${CMAKE_ROOT_DIR}/src/sxbCommon/utils.cpp
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
			

include_directories(${INC_DIR})

Add_Definitions(-D_HAS_ITERATOR_DEBUGGING=0)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_ROOT_DIR}/lib/x64)

add_library(${PROJECT_NAME} STATIC ${DIR_SRCS})

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "libs")


