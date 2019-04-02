
set(PROJECT_NAME Example02-HelloBGFX)

aux_source_directory(. DIR_SRCS)

set(DIR_SRCS ${DIR_SRCS} 
			 ${CMAKE_CURRENT_LIST_DIR}/cube.h)

set(INC_DIR ${CMAKE_ROOT_DIR}/bgfx/include 
			${CMAKE_ROOT_DIR}/bx/include 
			${CMAKE_ROOT_DIR}/bimg/include
			${CMAKE_ROOT_DIR}/sfml/include)
		
IF (WIN32)
    set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/bx/include/compat/msvc)
ELSEIF (APPLE)
    set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/bx/include/compat/osx)
ENDIF()
			
set(LINK_DIR ${CMAKE_ROOT_DIR}/lib/x64/Debug)

set(LINK_LIB bgfxDebug 
			 bimg_decodeDebug
			 bimgDebug
			 bxDebug
			 sfml-system-d
			 sfml-window-d)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})
link_libraries(${LINK_LIB})

Add_Definitions(-D_HAS_ITERATOR_DEBUGGING=0)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_ROOT_DIR}/bin/x64)

add_executable(${PROJECT_NAME} ${DIR_SRCS})

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "SxB")

