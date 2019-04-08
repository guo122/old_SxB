
set(PROJECT_NAME bgfx)

set(INCROOT ${CMAKE_ROOT_DIR}/include/bgfx)
set(SRCROOT ${CMAKE_ROOT_DIR}/src/bgfx)

set(DIR_SRCS 
	${INCROOT}/bgfx.h
	${SRCROOT}/bgfx.cpp
	${SRCROOT}/bgfx.idl.inl
	${SRCROOT}/bgfx_p.h
	${INCROOT}/defines.h
	${INCROOT}/embedded_shader.h
	${SRCROOT}/config.h
	${INCROOT}/platform.h
	${SRCROOT}/shader.h
	${SRCROOT}/shader.cpp
	${SRCROOT}/shader_dxbc.h
	${SRCROOT}/shader_dxbc.cpp
	${SRCROOT}/shader_dx9bc.h
	${SRCROOT}/shader_dx9bc.cpp
	${SRCROOT}/shader_spirv.h
	${SRCROOT}/shader_spirv.cpp
	${INCROOT}/vertexdecl.h
	${SRCROOT}/vertexdecl.cpp
	${SRCROOT}/topology.h
	${SRCROOT}/topology.cpp			 
	${SRCROOT}/vs_debugfont.bin.h
	${SRCROOT}/vs_debugfont.sc
	${SRCROOT}/fs_debugfont.bin.h
	${SRCROOT}/fs_debugfont.sc
	${SRCROOT}/vs_clear.bin.h
	${SRCROOT}/vs_clear.sc
	${SRCROOT}/fs_clear0.bin.h
	${SRCROOT}/fs_clear0.sc
	${SRCROOT}/fs_clear1.bin.h
	${SRCROOT}/fs_clear1.sc
	${SRCROOT}/fs_clear2.bin.h
	${SRCROOT}/fs_clear2.sc
	${SRCROOT}/fs_clear3.bin.h
	${SRCROOT}/fs_clear3.sc
	${SRCROOT}/fs_clear4.bin.h
	${SRCROOT}/fs_clear4.sc
	${SRCROOT}/fs_clear5.bin.h
	${SRCROOT}/fs_clear5.sc
	${SRCROOT}/fs_clear6.bin.h
	${SRCROOT}/fs_clear6.sc
	${SRCROOT}/fs_clear7.bin.h
	${SRCROOT}/fs_clear7.sc
	${SRCROOT}/charset.h
	${SRCROOT}/renderer.h
	${SRCROOT}/renderer_d3d.h
	${SRCROOT}/renderer_d3d11.h
	${SRCROOT}/renderer_d3d11.cpp
	${SRCROOT}/renderer_d3d12.h
	${SRCROOT}/renderer_d3d12.cpp
	${SRCROOT}/renderer_d3d9.h
	${SRCROOT}/renderer_d3d9.cpp
	${SRCROOT}/renderer_gl.h
	${SRCROOT}/renderer_gl.cpp
	${SRCROOT}/renderer_gnm.cpp
	${SRCROOT}/renderer_mtl.h
	${SRCROOT}/renderer_mtl.mm
	${SRCROOT}/renderer_noop.cpp
	${SRCROOT}/renderer_nvn.cpp
	${SRCROOT}/renderer_vk.cpp
	${SRCROOT}/renderer_vk.h
	${SRCROOT}/debug_renderdoc.h
	${SRCROOT}/debug_renderdoc.cpp
	${SRCROOT}/glcontext_eagl.h
	${SRCROOT}/glcontext_eagl.mm
	${SRCROOT}/glcontext_egl.h
	${SRCROOT}/glcontext_egl.cpp
	${SRCROOT}/glcontext_glx.h
	${SRCROOT}/glcontext_glx.cpp
	${SRCROOT}/glcontext_nsgl.h
	${SRCROOT}/glcontext_nsgl.mm
	${SRCROOT}/glcontext_wgl.h
	${SRCROOT}/glcontext_wgl.cpp
	${SRCROOT}/glimports.h
	${SRCROOT}/nvapi.h
	${SRCROOT}/nvapi.cpp
	${SRCROOT}/dxgi.h
	${SRCROOT}/dxgi.cpp
	${SRCROOT}/varying.def.sc
	${INCROOT}/bgfx_utils.h
	${SRCROOT}/bgfx_utils.cpp
	${INCROOT}/dbg.h
)	

set(C99_SRCS
	${INCROOT}/c99/bgfx.h
)
source_group("c99" FILES ${C99_SRCS})		 

set(INC_DIR 
	${CMAKE_ROOT_DIR}/3rdparty/dxsdk/include
	${CMAKE_ROOT_DIR}/3rdparty/khronos
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
				-DBGFX_CONFIG_DEBUG=1
			)

sxb_add_library(
				${PROJECT_NAME} 
				FOLDER "libs" 
				SOURCES ${DIR_SRCS} ${C99_SRCS}
)
