
set(PROJECT_NAME sfml-window)

set(INCROOT ${CMAKE_ROOT_DIR}/include/SFML/Window)
set(SRCROOT ${CMAKE_ROOT_DIR}/src/SFML/Window)

set(DIR_SRCS 
			${INCROOT}/Export.hpp
			${INCROOT}/WindowBase.hpp
			${SRCROOT}/WindowBase.cpp
			${INCROOT}/Cursor.hpp
			${SRCROOT}/Cursor.cpp
			${SRCROOT}/CursorImpl.hpp
			${INCROOT}/VideoMode.hpp
			${SRCROOT}/VideoMode.cpp
			${SRCROOT}/VideoModeImpl.hpp
			${INCROOT}/WindowHandle.hpp
			${INCROOT}/WindowStyle.hpp
			${SRCROOT}/WindowImpl.hpp
			${SRCROOT}/WindowImpl.cpp
			${INCROOT}/ContextSettings.hpp
			${INCROOT}/Event.hpp
			${INCROOT}/Joystick.hpp
			${SRCROOT}/Joystick.cpp
			${SRCROOT}/JoystickImpl.hpp
			${SRCROOT}/JoystickManager.hpp
			${SRCROOT}/JoystickManager.cpp
			${INCROOT}/Keyboard.hpp
			${SRCROOT}/Keyboard.cpp
			${SRCROOT}/InputImpl.hpp
			${INCROOT}/Mouse.hpp
			${SRCROOT}/Mouse.cpp
			${INCROOT}/Sensor.hpp
			${SRCROOT}/Sensor.cpp
			${SRCROOT}/SensorImpl.hpp
			${SRCROOT}/SensorManager.hpp
			${SRCROOT}/SensorManager.cpp
			${SRCROOT}/GlContext.hpp
			${SRCROOT}/GlContext.cpp
			${INCROOT}/Context.hpp
			${SRCROOT}/Context.cpp
			${INCROOT}/GlResource.hpp
			${SRCROOT}/GlResource.cpp
)
			 
# add platform specific sources
if(SXB_OS_WINDOWS)
    set(PLATFORM_SRC
        ${SRCROOT}/Win32/CursorImpl.hpp
        ${SRCROOT}/Win32/CursorImpl.cpp
        ${SRCROOT}/Win32/VideoModeImpl.cpp
        ${SRCROOT}/Win32/JoystickImpl.hpp
        ${SRCROOT}/Win32/JoystickImpl.cpp
        ${SRCROOT}/Win32/InputImpl.hpp
        ${SRCROOT}/Win32/InputImpl.cpp
        ${SRCROOT}/Win32/SensorImpl.hpp
        ${SRCROOT}/Win32/SensorImpl.cpp
        ${SRCROOT}/Win32/WindowImplWin32.hpp
        ${SRCROOT}/Win32/WindowImplWin32.cpp
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
		${SRCROOT}/OSX/AutoreleasePoolWrapper.h
		${SRCROOT}/OSX/AutoreleasePoolWrapper.mm
		${SRCROOT}/OSX/cpp_objc_conversion.h
		${SRCROOT}/OSX/cpp_objc_conversion.mm
		${SRCROOT}/OSX/cg_sf_conversion.hpp
		${SRCROOT}/OSX/cg_sf_conversion.mm
		${SRCROOT}/OSX/CursorImpl.hpp
		${SRCROOT}/OSX/CursorImpl.mm
		${SRCROOT}/OSX/VideoModeImpl.cpp
		${SRCROOT}/OSX/JoystickImpl.hpp
		${SRCROOT}/OSX/JoystickImpl.cpp
		${SRCROOT}/OSX/InputImpl.hpp
		${SRCROOT}/OSX/InputImpl.mm
		${SRCROOT}/OSX/HIDInputManager.hpp
		${SRCROOT}/OSX/HIDInputManager.mm
		${SRCROOT}/OSX/HIDJoystickManager.hpp
		${SRCROOT}/OSX/HIDJoystickManager.cpp
		${SRCROOT}/OSX/NSImage+raw.h
		${SRCROOT}/OSX/NSImage+raw.mm
		${SRCROOT}/OSX/Scaling.h
		${SRCROOT}/OSX/SensorImpl.hpp
		${SRCROOT}/OSX/SensorImpl.cpp
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
		${SRCROOT}/OSX/SFOpenGLView+mouse.mm
        ${SRCROOT}/OSX/SFOpenGLView+mouse_priv.h
        ${SRCROOT}/OSX/SFSilentResponder.h
        ${SRCROOT}/OSX/SFSilentResponder.m
		${SRCROOT}/OSX/SFWindowController.h
		${SRCROOT}/OSX/SFWindowController.mm
		${SRCROOT}/OSX/SFViewController.h
		${SRCROOT}/OSX/SFViewController.mm
		${SRCROOT}/OSX/SFWindow.h
		${SRCROOT}/OSX/SFWindow.m
		${SRCROOT}/OSX/WindowImplCocoa.hpp
		${SRCROOT}/OSX/WindowImplCocoa.mm
		${SRCROOT}/OSX/WindowImplDelegateProtocol.h
	)
	source_group("mac" FILES ${PLATFORM_SRC})
elseif(SXB_OS_IOS)
	set(PLATFORM_SRC
        ${SRCROOT}/iOS/CursorImpl.hpp
        ${SRCROOT}/iOS/CursorImpl.cpp
        ${SRCROOT}/iOS/VideoModeImpl.mm
        ${SRCROOT}/iOS/JoystickImpl.hpp
        ${SRCROOT}/iOS/JoystickImpl.mm
        ${SRCROOT}/iOS/SensorImpl.hpp
        ${SRCROOT}/iOS/SensorImpl.mm
		${SRCROOT}/iOS/SFView.hpp
		${SRCROOT}/iOS/SFView.mm
		${SRCROOT}/iOS/EaglContext.hpp
		${SRCROOT}/iOS/EaglContext.mm
        ${SRCROOT}/iOS/WindowImplUIKit.hpp
        ${SRCROOT}/iOS/WindowImplUIKit.mm
    )
    source_group("ios" FILES ${PLATFORM_SRC})
elseif(SXB_OS_ANDROID)
	set(PLATFORM_SRC
        ${SRCROOT}/Android/CursorImpl.hpp
        ${SRCROOT}/Android/CursorImpl.cpp
        ${SRCROOT}/Android/VideoModeImpl.cpp
        ${SRCROOT}/Android/JoystickImpl.hpp
        ${SRCROOT}/Android/JoystickImpl.cpp
        ${SRCROOT}/Android/InputImpl.hpp
        ${SRCROOT}/Android/InputImpl.cpp
        ${SRCROOT}/Android/SensorImpl.hpp
        ${SRCROOT}/Android/SensorImpl.cpp
        ${SRCROOT}/Android/WindowImplAndroid.hpp
        ${SRCROOT}/Android/WindowImplAndroid.cpp
    )
    source_group("android" FILES ${PLATFORM_SRC})
endif()

set(INC_DIR 
	${CMAKE_ROOT_DIR}/src
)

include_directories(${INC_DIR})

sxb_add_library(
				${PROJECT_NAME} 
				SHARED INSTALL 
				FOLDER "libs" 
				SOURCES ${DIR_SRCS} ${PLATFORM_SRC}
)

target_link_libraries(${PROJECT_NAME} PUBLIC sfml-system)
if(SXB_OS_WINDOWS)
	target_link_libraries(${PROJECT_NAME} PRIVATE winmm gdi32)
elseif(SXB_OS_MACOS)
	target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Foundation" "-framework AppKit" "-framework IOKit" "-framework Carbon")
endif()

