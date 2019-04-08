
set(PROJECT_NAME bimg)

set(INCROOT ${CMAKE_ROOT_DIR}/include/bimg)
set(SRCROOT ${CMAKE_ROOT_DIR}/src/bimg)

set(DIR_SRCS 
	${INCROOT}/bimg.h
	${INCROOT}/decode.h
	${INCROOT}/encode.h
	${SRCROOT}/bimg_p.h
	${SRCROOT}/image.cpp
	${SRCROOT}/image_cubemap_filter.cpp
	${SRCROOT}/image_decode.cpp
	${SRCROOT}/image_gnf.cpp
)

set(ASTC_DECODE_SRC
					${SRCROOT}/astc-decoder/astc_file.cc
					${SRCROOT}/astc-decoder/astc_file.h
					${SRCROOT}/astc-decoder/codec.cc
					${SRCROOT}/astc-decoder/codec.h
					${SRCROOT}/astc-decoder/endpoint_codec.cc
					${SRCROOT}/astc-decoder/endpoint_codec.h
					${SRCROOT}/astc-decoder/footprint.cc
					${SRCROOT}/astc-decoder/footprint.h
					${SRCROOT}/astc-decoder/integer_sequence_codec.cc
					${SRCROOT}/astc-decoder/integer_sequence_codec.h
					${SRCROOT}/astc-decoder/intermediate_astc_block.cc
					${SRCROOT}/astc-decoder/intermediate_astc_block.h
					${SRCROOT}/astc-decoder/logical_astc_block.cc
					${SRCROOT}/astc-decoder/logical_astc_block.h
					${SRCROOT}/astc-decoder/partition.cc
					${SRCROOT}/astc-decoder/partition.h
					${SRCROOT}/astc-decoder/physical_astc_block.cc
					${SRCROOT}/astc-decoder/physical_astc_block.h
					${SRCROOT}/astc-decoder/quantization.cc
					${SRCROOT}/astc-decoder/quantization.h
					${SRCROOT}/astc-decoder/weight_infill.cc
					${SRCROOT}/astc-decoder/weight_infill.h
					${SRCROOT}/astc-decoder/types.h	 
)
source_group("astc-decode" FILES ${ASTC_DECODE_SRC})	

set(ASTC_BASE_SRC
				${SRCROOT}/astc-base/bit_stream.h
				${SRCROOT}/astc-base/bottom_n.h
				${SRCROOT}/astc-base/math_utils.h
				${SRCROOT}/astc-base/optional.h
				${SRCROOT}/astc-base/string_utils.h
				${SRCROOT}/astc-base/type_traits.h
				${SRCROOT}/astc-base/uint128.h
				${SRCROOT}/astc-base/utils.h
)
source_group("astc-base" FILES ${ASTC_BASE_SRC})	
 
set(INC_DIR 
	${CMAKE_ROOT_DIR}/include/bimg
	${CMAKE_ROOT_DIR}/src/bimg
)

IF (SXB_OS_WINDOWS)
	set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/include/bx/compat/msvc)
ENDIF()

include_directories(${INC_DIR})

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

sxb_add_library(
				${PROJECT_NAME} 
				FOLDER "libs" 
				SOURCES ${DIR_SRCS} ${ASTC_DECODE_SRC} ${ASTC_BASE_SRC}
)

