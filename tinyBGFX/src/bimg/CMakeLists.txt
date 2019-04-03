
set(PROJECT_NAME tinyBGFX_bimg)

set(DIR_SRCS ${CMAKE_ROOT_DIR}/tinyBGFX/include/bimg/bimg.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/bimg_p.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/image.cpp
			 )			 

set(INC_DIR ${CMAKE_ROOT_DIR}/tinyBGFX/include
			${CMAKE_ROOT_DIR}/tinyBGFX/include/bimg
			${CMAKE_ROOT_DIR}/bimg/3rdparty/astc-codec
			${CMAKE_ROOT_DIR}/bimg/3rdparty/astc-codec/include
			)

IF (WIN32)
	set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/compat/msvc)
ENDIF()
			
#set(LINK_LIB winmm)

include_directories(${INC_DIR})
#link_directories(${LINK_DIR})
#link_libraries(${LINK_LIB})

Add_Definitions(-D__STDC_LIMIT_MACROS
				-D__STDC_FORMAT_MACROS
				-D__STDC_CONSTANT_MACROS
				-D_HAS_EXCEPTIONS=0
				-D_HAS_ITERATOR_DEBUGGING=0
				-D_ITERATOR_DEBUG_LEVEL=0
				-D_SCL_SECURE=0
				-D_SECURE_SCL=0
				-D_SCL_SECURE_NO_WARNINGS
				-D_CRT_SECURE_NO_WARNINGS
				-D_CRT_SECURE_NO_DEPRECATE
				)


SET(LIBRARY_OUTPUT_PATH ${CMAKE_ROOT_DIR}/lib/x64)
#SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_ROOT_DIR}/bin/x64)

add_library(${PROJECT_NAME} STATIC ${DIR_SRCS})
#add_library(${PROJECT_NAME} SHARED ${DIR_SRCS})

#INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_ROOT_DIR}/bin/x64/Debug)
#INSTALL(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_ROOT_DIR}/bin/x64)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "tinyBGFX")

