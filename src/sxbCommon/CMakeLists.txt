
set(PROJECT_NAME sxbCommon)

set(DIR_SRCS ${CMAKE_ROOT_DIR}/include/sxbTop/defines.h
			 ${CMAKE_ROOT_DIR}/include/sxbCommon/utils.h
			 ${CMAKE_ROOT_DIR}/src/sxbCommon/utils.cpp
			 ${CMAKE_ROOT_DIR}/include/sxbCommon/Mesh.h
			 ${CMAKE_ROOT_DIR}/src/sxbCommon/Mesh.cpp
			)
			
set(ID_COMPRESS_SRCS ${CMAKE_ROOT_DIR}/3rdparty/ib-compress/indexbuffercompression.cpp
					 ${CMAKE_ROOT_DIR}/3rdparty/ib-compress/indexbuffercompression.h
					 ${CMAKE_ROOT_DIR}/3rdparty/ib-compress/indexbuffercompressionformat.h
					 ${CMAKE_ROOT_DIR}/3rdparty/ib-compress/indexbufferdecompression.cpp
					 ${CMAKE_ROOT_DIR}/3rdparty/ib-compress/indexbufferdecompression.h
					 ${CMAKE_ROOT_DIR}/3rdparty/ib-compress/indexcompressionconstants.h
					 ${CMAKE_ROOT_DIR}/3rdparty/ib-compress/readbitstream.h
					 ${CMAKE_ROOT_DIR}/3rdparty/ib-compress/writebitstream.h
			)
			
source_group("ib-compress" FILES ${ID_COMPRESS_SRCS})	
			
set(DIR_SRCS ${DIR_SRCS} ${ID_COMPRESS_SRCS})

set(INC_DIR ${CMAKE_ROOT_DIR}/include 
			${CMAKE_ROOT_DIR}/3rdparty 
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

sxb_add_library(
				${PROJECT_NAME} 
				FOLDER "libs" 
				SOURCES ${DIR_SRCS}
)