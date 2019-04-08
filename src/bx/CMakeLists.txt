
set(PROJECT_NAME bx)

set(INCROOT ${CMAKE_ROOT_DIR}/include/bx)
set(SRCROOT ${CMAKE_ROOT_DIR}/src/bx)

set(DIR_SRCS 
			${INCROOT}/platform.h
			${INCROOT}/macros.h
			${INCROOT}/bx.h
			${SRCROOT}/bx_p.h
			${SRCROOT}/bx.cpp
			${INCROOT}/debug.h
			${SRCROOT}/debug.cpp
			${INCROOT}/bxstring.h
			${SRCROOT}/bxstring.cpp
			${INCROOT}/allocator.h
			${SRCROOT}/allocator.cpp
			${INCROOT}/hash.h
			${SRCROOT}/hash.cpp
			${INCROOT}/readerwriter.h
			${INCROOT}/endian.h
			${INCROOT}/error.h
			${INCROOT}/filepath.h
			${SRCROOT}/filepath.cpp
			${INCROOT}/file.h
			${SRCROOT}/file.cpp
			${INCROOT}/os.h
			${SRCROOT}/os.cpp
			${INCROOT}/uint32_t.h
			${INCROOT}/config.h
			${INCROOT}/math.h
			${SRCROOT}/math.cpp
			${INCROOT}/simd_t.h
			${INCROOT}/cpu.h
			${INCROOT}/float4x4_t.h
			${INCROOT}/handlealloc.h
			${INCROOT}/mutex.h
			${SRCROOT}/mutex.cpp
			${INCROOT}/ringbuffer.h
			${INCROOT}/sort.h
			${SRCROOT}/sort.cpp
			${INCROOT}/thread.h
			${SRCROOT}/thread.cpp
			${INCROOT}/mpscqueue.h
			${INCROOT}/spscqueue.h
			${INCROOT}/semaphore.h
			${SRCROOT}/semaphore.cpp
			${INCROOT}/timer.h
			${SRCROOT}/timer.cpp
			${INCROOT}/pixelformat.h
			${INCROOT}/rng.h
			${INCROOT}/easing.h
			${SRCROOT}/easing.cpp
			${INCROOT}/process.h
			${SRCROOT}/process.cpp
			${INCROOT}/maputil.h
			${INCROOT}/commandline.h
			${SRCROOT}/commandline.cpp
			${INCROOT}/settings.h
			${SRCROOT}/settings.cpp
			${INCROOT}/url.h
			${SRCROOT}/url.cpp
			${SRCROOT}/crtnone.cpp
			${SRCROOT}/dtoa.cpp
)	
			 
set(INLINE_SRC
			${INCROOT}/inline/bx.inl
			${INCROOT}/inline/bxstring.inl
			${INCROOT}/inline/allocator.inl
			${INCROOT}/inline/hash.inl
			${INCROOT}/inline/readerwriter.inl
			${INCROOT}/inline/endian.inl
			${INCROOT}/inline/error.inl
			${INCROOT}/inline/uint32_t.inl
			${INCROOT}/inline/math.inl
			${INCROOT}/inline/simd128_swizzle.inl
			${INCROOT}/inline/simd128_sse.inl
			${INCROOT}/inline/simd128_ref.inl
			${INCROOT}/inline/simd256_ref.inl
			${INCROOT}/inline/simd_ni.inl
			${INCROOT}/inline/cpu.inl
			${INCROOT}/inline/float4x4_t.inl
			${INCROOT}/inline/handlealloc.inl
			${INCROOT}/inline/mutex.inl
			${INCROOT}/inline/ringbuffer.inl
			${INCROOT}/inline/sort.inl
			${INCROOT}/inline/mpscqueue.inl
			${INCROOT}/inline/spscqueue.inl
			${INCROOT}/inline/pixelformat.inl
			${INCROOT}/inline/rng.inl
			${INCROOT}/inline/easing.inl
			${INCROOT}/inline/simd128_langext.inl
			${INCROOT}/inline/simd128_neon.inl
			${INCROOT}/inline/simd256_avx.inl
)
source_group("inline" FILES ${INLINE_SRC})

set(TINYSTL_SRC
			 ${INCROOT}/../tinystl/allocator.h
			 ${INCROOT}/../tinystl/buffer.h
			 ${INCROOT}/../tinystl/hash.h
			 ${INCROOT}/../tinystl/LICENSE
			 ${INCROOT}/../tinystl/new.h
			 ${INCROOT}/../tinystl/stddef.h
			 ${INCROOT}/../tinystl/string.h
			 ${INCROOT}/../tinystl/traits.h
			 ${INCROOT}/../tinystl/unordered_map.h
			 ${INCROOT}/../tinystl/unordered_set.h
			 ${INCROOT}/../tinystl/vector.h
)
source_group("tinystl" FILES ${TINYSTL_SRC})

# add platform specific sources
if(WIN32)
    set(PLATFORM_SRC
        ${INCROOT}/compat/msvc/alloca.h
        ${INCROOT}/compat/msvc/dirent.h
        ${INCROOT}/compat/msvc/inttypes.h
        ${INCROOT}/compat/msvc/stdbool.h
        ${INCROOT}/compat/msvc/pre1600/stdint.h
    )
    source_group("msvc" FILES ${PLATFORM_SRC})
endif()		 

IF (SXB_OS_WINDOWS)
	set(INC_DIR ${CMAKE_ROOT_DIR}/include/bx/compat/msvc)
ELSEIF (SXB_OS_MACOS)
	set(INC_DIR ${CMAKE_ROOT_DIR}/include/bx/compat/osx)
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
				-DBX_CONFIG_DEBUG=1
				)

sxb_add_library(
				${PROJECT_NAME} 
				FOLDER "libs" 
				SOURCES ${DIR_SRCS} ${PLATFORM_SRC} ${INLINE_SRC} ${TINYSTL_SRC}
)