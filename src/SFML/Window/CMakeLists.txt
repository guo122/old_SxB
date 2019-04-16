
set(PROJECT_NAME sfml-window)

set(INCROOT ${CMAKE_ROOT_DIR}/include/SFML/Window)
set(SRCROOT ${CMAKE_ROOT_DIR}/src/SFML/Window)

set(DIR_SRCS 
	${INCROOT}/Clipboard.hpp
    ${SRCROOT}/Clipboard.cpp
    ${SRCROOT}/ClipboardImpl.hpp
    ${SRCROOT}/Context.cpp
    ${INCROOT}/Context.hpp
    ${SRCROOT}/Cursor.cpp
    ${INCROOT}/Cursor.hpp
    ${SRCROOT}/CursorImpl.hpp
    ${INCROOT}/Export.hpp
    ${SRCROOT}/GlContext.cpp
    ${SRCROOT}/GlContext.hpp
    ${SRCROOT}/GlResource.cpp
    ${INCROOT}/GlResource.hpp
    ${INCROOT}/ContextSettings.hpp
    ${INCROOT}/Event.hpp
    ${SRCROOT}/InputImpl.hpp
    ${INCROOT}/Joystick.hpp
    ${SRCROOT}/Joystick.cpp
    ${SRCROOT}/JoystickImpl.hpp
    ${SRCROOT}/JoystickManager.cpp
    ${SRCROOT}/JoystickManager.hpp
    ${INCROOT}/Keyboard.hpp
    ${SRCROOT}/Keyboard.cpp
    ${INCROOT}/Mouse.hpp
    ${SRCROOT}/Mouse.cpp
    ${INCROOT}/Touch.hpp
    ${SRCROOT}/Touch.cpp
    ${INCROOT}/Sensor.hpp
    ${SRCROOT}/Sensor.cpp
    ${SRCROOT}/SensorImpl.hpp
    ${SRCROOT}/SensorManager.cpp
    ${SRCROOT}/SensorManager.hpp
    ${SRCROOT}/VideoMode.cpp
    ${INCROOT}/VideoMode.hpp
    ${SRCROOT}/VideoModeImpl.hpp
    ${SRCROOT}/Window.cpp
    ${INCROOT}/Window.hpp
    ${SRCROOT}/WindowBase.cpp
    ${INCROOT}/WindowBase.hpp
    ${INCROOT}/WindowHandle.hpp
    ${SRCROOT}/WindowImpl.cpp
    ${SRCROOT}/WindowImpl.hpp
    ${INCROOT}/WindowStyle.hpp
)

#todo
if(SFML_OPENGL_ES AND NOT SXB_OS_IOS)
    list(APPEND DIR_SRCS ${SRCROOT}/EGLCheck.cpp)
	list(APPEND DIR_SRC ${SRCROOT}/EGLCheck.hpp)
    list(APPEND DIR_SRC ${SRCROOT}/EglContext.cpp)
    list(APPEND DIR_SRC ${SRCROOT}/EglContext.hpp)
endif()
source_group("" FILES ${DIR_SRC})
			 
# add platform specific sources
if(SXB_OS_WINDOWS)
    set(PLATFORM_SRC
		        ${SRCROOT}/Win32/CursorImpl.hpp
        ${SRCROOT}/Win32/CursorImpl.cpp
        ${SRCROOT}/Win32/ClipboardImpl.hpp
        ${SRCROOT}/Win32/ClipboardImpl.cpp
        ${SRCROOT}/Win32/WglContext.cpp
        ${SRCROOT}/Win32/WglContext.hpp
        ${SRCROOT}/Win32/WglExtensions.cpp
        ${SRCROOT}/Win32/WglExtensions.hpp
        ${SRCROOT}/Win32/InputImpl.cpp
        ${SRCROOT}/Win32/InputImpl.hpp
        ${SRCROOT}/Win32/JoystickImpl.cpp
        ${SRCROOT}/Win32/JoystickImpl.hpp
        ${SRCROOT}/Win32/SensorImpl.hpp
        ${SRCROOT}/Win32/SensorImpl.cpp
        ${SRCROOT}/Win32/VideoModeImpl.cpp
        ${SRCROOT}/Win32/WindowImplWin32.cpp
        ${SRCROOT}/Win32/WindowImplWin32.hpp
	)
    source_group("windows" FILES ${PLATFORM_SRC})
	Add_Definitions(-DUNICODE -D_UNICODE)
elseif(SXB_OS_LINUX)
    set(PLATFORM_SRC
        ${SRCROOT}/Unix/CursorImpl.hpp
        ${SRCROOT}/Unix/CursorImpl.cpp
        ${SRCROOT}/Unix/VideoModeImpl.cpp
        ${SRCROOT}/Unix/JoystickImpl.hpp
        ${SRCROOT}/Unix/JoystickImpl.cpp
        ${SRCROOT}/Unix/InputImpl.hpp
        ${SRCROOT}/Unix/InputImpl.cpp
        ${SRCROOT}/Unix/SensorImpl.hpp
        ${SRCROOT}/Unix/SensorImpl.cpp
        ${SRCROOT}/Unix/WindowImplX11.hpp
        ${SRCROOT}/Unix/WindowImplX11.cpp
	)
    source_group("unix" FILES ${PLATFORM_SRC})
elseif(SXB_OS_MACOS)
	set(PLATFORM_SRC
		        ${SRCROOT}/OSX/cpp_objc_conversion.h
        ${SRCROOT}/OSX/cpp_objc_conversion.mm
        ${SRCROOT}/OSX/cg_sf_conversion.hpp
        ${SRCROOT}/OSX/cg_sf_conversion.mm
        ${SRCROOT}/OSX/CursorImpl.hpp
        ${SRCROOT}/OSX/CursorImpl.mm
        ${SRCROOT}/OSX/ClipboardImpl.hpp
        ${SRCROOT}/OSX/ClipboardImpl.mm
        ${SRCROOT}/OSX/InputImpl.mm
        ${SRCROOT}/OSX/InputImpl.hpp
        ${SRCROOT}/OSX/HIDInputManager.hpp
        ${SRCROOT}/OSX/HIDInputManager.mm
        ${SRCROOT}/OSX/HIDJoystickManager.hpp
        ${SRCROOT}/OSX/HIDJoystickManager.cpp
        ${SRCROOT}/OSX/JoystickImpl.cpp
        ${SRCROOT}/OSX/JoystickImpl.hpp
        ${SRCROOT}/OSX/NSImage+raw.h
        ${SRCROOT}/OSX/NSImage+raw.mm
        ${SRCROOT}/OSX/Scaling.h
        ${SRCROOT}/OSX/SensorImpl.cpp
        ${SRCROOT}/OSX/SensorImpl.hpp
        ${SRCROOT}/OSX/SFApplication.h
        ${SRCROOT}/OSX/SFApplication.m
        ${SRCROOT}/OSX/SFApplicationDelegate.h
        ${SRCROOT}/OSX/SFApplicationDelegate.m
        ${SRCROOT}/OSX/SFContext.hpp
        ${SRCROOT}/OSX/SFContext.mm
        ${SRCROOT}/OSX/SFKeyboardModifiersHelper.h
        ${SRCROOT}/OSX/SFKeyboardModifiersHelper.mm
        ${SRCROOT}/OSX/SFOpenGLView.h
        ${SRCROOT}/OSX/SFOpenGLView.mm
        ${SRCROOT}/OSX/SFOpenGLView+keyboard.mm
        ${SRCROOT}/OSX/SFOpenGLView+keyboard_priv.h
        ${SRCROOT}/OSX/SFOpenGLView+mouse.mm
        ${SRCROOT}/OSX/SFOpenGLView+mouse_priv.h
        ${SRCROOT}/OSX/SFSilentResponder.h
        ${SRCROOT}/OSX/SFSilentResponder.m
        ${SRCROOT}/OSX/SFWindow.h
        ${SRCROOT}/OSX/SFWindow.m
        ${SRCROOT}/OSX/SFWindowController.h
        ${SRCROOT}/OSX/SFWindowController.mm
        ${SRCROOT}/OSX/SFViewController.h
        ${SRCROOT}/OSX/SFViewController.mm
        ${SRCROOT}/OSX/VideoModeImpl.cpp
        ${SRCROOT}/OSX/WindowImplCocoa.hpp
        ${SRCROOT}/OSX/WindowImplCocoa.mm
        ${SRCROOT}/OSX/WindowImplDelegateProtocol.h
        ${SRCROOT}/OSX/AutoreleasePoolWrapper.h
        ${SRCROOT}/OSX/AutoreleasePoolWrapper.mm
	)
	source_group("mac" FILES ${PLATFORM_SRC})
elseif(SXB_OS_IOS)
	set(PLATFORM_SRC
		        ${SRCROOT}/iOS/CursorImpl.hpp
        ${SRCROOT}/iOS/CursorImpl.cpp
        ${SRCROOT}/iOS/ClipboardImpl.mm
        ${SRCROOT}/iOS/ClipboardImpl.hpp
        ${SRCROOT}/iOS/EaglContext.mm
        ${SRCROOT}/iOS/EaglContext.hpp
        ${SRCROOT}/iOS/InputImpl.mm
        ${SRCROOT}/iOS/InputImpl.hpp
        ${SRCROOT}/iOS/JoystickImpl.mm
        ${SRCROOT}/iOS/JoystickImpl.hpp
        ${SRCROOT}/iOS/SensorImpl.mm
        ${SRCROOT}/iOS/SensorImpl.hpp
        ${SRCROOT}/iOS/VideoModeImpl.mm
        ${SRCROOT}/iOS/WindowImplUIKit.hpp
        ${SRCROOT}/iOS/WindowImplUIKit.mm
        ${SRCROOT}/iOS/ObjCType.hpp
        ${SRCROOT}/iOS/SFAppDelegate.hpp
        ${SRCROOT}/iOS/SFAppDelegate.mm
        ${SRCROOT}/iOS/SFView.hpp
        ${SRCROOT}/iOS/SFView.mm
        ${SRCROOT}/iOS/SFViewController.hpp
        ${SRCROOT}/iOS/SFViewController.mm
        ${SRCROOT}/iOS/SFMain.hpp
        ${SRCROOT}/iOS/SFMain.mm
    )
    source_group("ios" FILES ${PLATFORM_SRC})
elseif(SXB_OS_ANDROID)
	set(PLATFORM_SRC
		        ${SRCROOT}/Android/CursorImpl.hpp
        ${SRCROOT}/Android/CursorImpl.cpp
        ${SRCROOT}/Android/ClipboardImpl.hpp
        ${SRCROOT}/Android/ClipboardImpl.cpp
        ${SRCROOT}/Android/WindowImplAndroid.hpp
        ${SRCROOT}/Android/WindowImplAndroid.cpp
        ${SRCROOT}/Android/VideoModeImpl.cpp
        ${SRCROOT}/Android/InputImpl.hpp
        ${SRCROOT}/Android/InputImpl.cpp
        ${SRCROOT}/Android/JoystickImpl.hpp
        ${SRCROOT}/Android/JoystickImpl.cpp
        ${SRCROOT}/Android/SensorImpl.hpp
        ${SRCROOT}/Android/SensorImpl.cpp
    )
    source_group("android" FILES ${PLATFORM_SRC})
endif()

if (SXB_OS_WINDOWS)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_ROOT_DIR}/extlibs/headers")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_ROOT_DIR}/extlibs/libs-osx/lib/")
elseif(SXB_OS_IOS)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_ROOT_DIR}/extlibs/headers")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_ROOT_DIR}/extlibs/libs-ios/")
endif()

# define the path of our additional CMake modules
set(CMAKE_MODULE_PATH "${CMAKE_ROOT_DIR}/cmake/Modules/")

set(INC_DIR 
	${CMAKE_ROOT_DIR}/src
	${CMAKE_ROOT_DIR}/3rdparty/khronos
)

include_directories(${INC_DIR})

if(SXB_OS_WINDOWS)
sxb_add_library(
				${PROJECT_NAME} 
				SHARED INSTALL
				FOLDER "libs" 
				SOURCES ${DIR_SRCS} ${PLATFORM_SRC}
)
else()
sxb_add_library(
				${PROJECT_NAME} 
				FOLDER "libs" 
				SOURCES ${DIR_SRCS} ${PLATFORM_SRC}
)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC sfml-system)
if(SXB_OS_WINDOWS)
	target_link_libraries(${PROJECT_NAME} PRIVATE winmm gdi32)
elseif(SXB_OS_MACOS)
	target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Foundation" "-framework AppKit" "-framework IOKit" "-framework Carbon" -ObjC)
elseif(SXB_OS_IOS)
	target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Foundation" "-framework UIKit" "-framework CoreGraphics" "-framework QuartzCore" "-framework CoreMotion" "-framework Metal")
endif()

if(SFML_OPENGL_ES)
	if(SXB_OS_IOS)
		sfml_add_external(OpenGL LINK "-framework OpenGLES")
	elseif(SXB_OS_ANDROID)
		sfml_add_external(OpenGL LINK "EGL" "GLESv1_CM")
	endif()
else()
    sfml_find_package(OpenGL INCLUDE "OPENGL_INCLUDE_DIR" LINK "OPENGL_gl_LIBRARY")
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL)
