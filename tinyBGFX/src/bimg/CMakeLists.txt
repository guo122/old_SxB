
set(PROJECT_NAME tinyBGFX_bimg)

set(DIR_SRCS ${CMAKE_ROOT_DIR}/tinyBGFX/include/bimg/bimg.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bimg/decode.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bimg/encode.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/bimg_p.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/image.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/image_cubemap_filter.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/image_decode.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/image_gnf.cpp
			 )

set(ASTC_DECODE_SRC
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/astc_file.cc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/astc_file.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/codec.cc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/codec.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/endpoint_codec.cc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/endpoint_codec.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/footprint.cc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/footprint.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/integer_sequence_codec.cc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/integer_sequence_codec.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/intermediate_astc_block.cc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/intermediate_astc_block.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/logical_astc_block.cc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/logical_astc_block.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/partition.cc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/partition.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/physical_astc_block.cc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/physical_astc_block.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/quantization.cc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/quantization.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/weight_infill.cc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/weight_infill.h	 
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-decoder/types.h	 
    )
source_group("astc-decode" FILES ${ASTC_DECODE_SRC})	

set(ASTC_BASE_SRC
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-base/
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-base/bit_stream.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-base/bottom_n.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-base/math_utils.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-base/optional.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-base/string_utils.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-base/type_traits.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-base/uint128.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg/astc-base/utils.h
    )
source_group("astc-base" FILES ${ASTC_BASE_SRC})	

set(DIR_SRCS ${DIR_SRCS} ${ASTC_DECODE_SRC} ${ASTC_BASE_SRC})		 

set(INC_DIR ${CMAKE_ROOT_DIR}/tinyBGFX/include
			${CMAKE_ROOT_DIR}/tinyBGFX/include/bimg
			${CMAKE_ROOT_DIR}/tinyBGFX/src/bimg
			${CMAKE_ROOT_DIR}/bimg/3rdparty
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

