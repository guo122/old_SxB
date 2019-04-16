
set(PROJECT_NAME test_sfml)

set(SRCROOT ${CMAKE_ROOT_DIR}/test/test_sfml)

set(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++1y)

set(DIR_SRCS
    ${SRCROOT}/main.mm
    ${SRCROOT}/logo.h
)

set(INC_DIR
    ${CMAKE_ROOT_DIR}/src
)
IF (SXB_OS_WINDOWS)
    set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/include/bx/compat/msvc)
ELSEIF (SXB_OS_MACOS)
    set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/include/bx/compat/osx)
ENDIF()
include_directories(${INC_DIR})

set(LINK_LIBS
    bx
    bimg
    bgfx
    sfml-system
    sfml-window
)
if(SXB_OS_IOS)
    set(LINK_LIBS ${LINK_LIBS}
        sfml-main
    )
endif()
link_libraries(${LINK_LIBS})

Add_Definitions(
-D_HAS_ITERATOR_DEBUGGING=0
-DHAS_METAL_SDK
    -D__STDC_LIMIT_MACROS
    -D__STDC_FORMAT_MACROS
    -D__STDC_CONSTANT_MACROS
    -D_HAS_EXCEPTIONS=0
    -D_ITERATOR_DEBUG_LEVEL=0
    -D_SCL_SECURE=0
	    -D_SECURE_SCL=0
    -D_SCL_SECURE_NO_WARNINGS
    -D_CRT_SECURE_NO_WARNINGS
    -D_CRT_SECURE_NO_DEPRECATE
    -DBGFX_CONFIG_DEBUG=1
            -D__STDC_LIMIT_MACROS
        -D__STDC_FORMAT_MACROS
        -D__STDC_CONSTANT_MACROS
        -D_DEBUG
        -DBGFX_CONFIG_DEBUG=1
        -D_HAS_ITERATOR_DEBUGGING=0
        -DHAS_METAL_SDK
)
#set(APP_NAME "test_sfml")
#set(APP_BUNDLE_IDENTIFIER "quku.test_sfml")
#set(PRODUCT_NAME ${APP_NAME})
#set(EXECUTABLE_NAME ${APP_NAME})
#set(MACOSX_BUNDLE_EXECUTABLE_NAME ${APP_NAME})
#set(MACOSX_BUNDLE_INFO_STRING ${APP_BUNDLE_IDENTIFIER})
#set(MACOSX_BUNDLE_GUI_IDENTIFIER ${APP_BUNDLE_IDENTIFIER})
#set(MACOSX_BUNDLE_BUNDLE_NAME ${APP_BUNDLE_IDENTIFIER})
sxb_add_executable(
                ${PROJECT_NAME}
                FOLDER "test"
                SOURCES ${DIR_SRCS}
)

if(SXB_OS_WINDOWS)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm gdi32)
elseif(SXB_OS_MACOS)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Foundation" "-framework AppKit" "-framework IOKit" "-framework Carbon" "-framework Metal" "-framework QuartzCore")
	#elseif(SXB_OS_IOS)
	#target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Foundation" "-framework UIKit" "-framework CoreGraphics" "-framework QuartzCore" "-framework CoreMotion" "-framework Metal""-framework OpenGLES")
elseif(SXB_OS_ANDROID)
    target_link_libraries(${PROJECT_NAME} PRIVATE android)
endif()


#target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL)

set_property(TARGET ${PROJECT_NAME} PROPERTY XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_LAUNCHSCREEN_NAME LaunchScreen.xib)
