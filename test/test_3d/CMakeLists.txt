
set(PROJECT_NAME test_3d)

set(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++1y)

set(SRCROOT ${CMAKE_ROOT_DIR}/test/test_3d)

set(DIR_SRCS 
	${SRCROOT}/main.cpp
	${SRCROOT}/cube.h
	${SRCROOT}/cube.cpp
)

IF (SXB_OS_WINDOWS)
	set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/include/bx/compat/msvc)
ELSEIF (SXB_OS_MACOS)
	set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/include/bx/compat/osx)
ENDIF()

set(LINK_LIBS 
	bgfx
	bx
	bimg
	sfml-system
	sfml-window
	sxbCommon
)
if(SXB_OS_IOS)
    set(LINK_LIBS ${LINK_LIBS}
        sfml-main
    )
endif()

include_directories(${INC_DIR})
link_libraries(${LINK_LIBS})

Add_Definitions(
	-D_HAS_ITERATOR_DEBUGGING=0
	-DBGFX_CONFIG_RENDERER_METAL=1
)

sxb_add_executable(
				${PROJECT_NAME} 
				FOLDER "test" 
				SOURCES ${DIR_SRCS}
)

if(SXB_OS_WINDOWS)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm gdi32)
elseif(SXB_OS_MACOS)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Foundation" "-framework AppKit" "-framework IOKit" "-framework Carbon" "-framework Metal" "-framework QuartzCore")
elseif(SXB_OS_IOS)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Foundation" "-framework UIKit" "-framework CoreGraphics" "-framework QuartzCore" "-framework CoreMotion" "-framework Metal" "-framework OpenGLES" "-framework OpenAL")
elseif(SXB_OS_ANDROID)
    target_link_libraries(${PROJECT_NAME} PRIVATE android)
endif()
