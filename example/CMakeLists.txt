
set(EXAMPLE_INC_DIR 
	${CMAKE_ROOT_DIR}/3rdparty
	${CMAKE_ROOT_DIR}/include
)

set(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++1y)

IF (SXB_OS_WINDOWS)
	set(EXAMPLE_INC_DIR ${EXAMPLE_INC_DIR} ${CMAKE_ROOT_DIR}/include/bx/compat/msvc)
ELSEIF (SXB_OS_MACOS)
	set(EXAMPLE_INC_DIR ${EXAMPLE_INC_DIR} ${CMAKE_ROOT_DIR}/include/bx/compat/osx)
ENDIF()

set(EXAMPLE_LINK_LIBS 
	bgfx
	bx
	bimg
	sfml-system
	sfml-window
	sxbCommon
)
if(SXB_OS_IOS)
	set(EXAMPLE_LINK_LIBS ${EXAMPLE_LINK_LIBS}
		sfml-main
	)
endif()

include_directories(${EXAMPLE_INC_DIR})
link_libraries(${EXAMPLE_LINK_LIBS})

if(SXB_OS_WINDOWS)
    link_libraries(winmm gdi32)
elseif(SXB_OS_MACOS)
    link_libraries("-framework Foundation" "-framework AppKit" "-framework IOKit" "-framework Carbon" "-framework Metal" "-framework QuartzCore")
elseif(SXB_OS_IOS)
    link_libraries("-framework Foundation" "-framework UIKit" "-framework CoreGraphics" "-framework QuartzCore" "-framework CoreMotion" "-framework Metal" "-framework OpenGLES" "-framework OpenAL")
elseif(SXB_OS_ANDROID)
    link_libraries(  android)
endif()

	
add_subdirectory("example_00-HelloBGFX")
add_subdirectory("example_00-HelloWorld")
add_subdirectory("example_11-bob")
add_subdirectory("example_11-coc")
add_subdirectory("example_12-lod")
add_subdirectory("example_13-stencil")
add_subdirectory("example_33-pom")
