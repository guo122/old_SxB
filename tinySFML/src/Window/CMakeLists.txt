
set(PROJECT_NAME tinySFML_Window)

set(INCROOT ${CMAKE_ROOT_DIR}/tinySFML/include/Window)
set(SRCROOT ${CMAKE_ROOT_DIR}/tinySFML/src/Window)

set(DIR_SRCS 
	${CMAKE_ROOT_DIR}/tinySFML/include/Config.hpp
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
else()
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
endif()

set(INC_DIR 
	${CMAKE_ROOT_DIR}/tinySFML/include
	${CMAKE_ROOT_DIR}/tinySFML/src
)
include_directories(${INC_DIR})

#_UNICODE
Add_Definitions(-DUNICODE -D_UNICODE)

if(SXB_OS_WINDOWS)
	SET(LIBRARY_OUTPUT_PATH ${CMAKE_ROOT_DIR}/lib/win64)
else()
	SET(LIBRARY_OUTPUT_PATH ${CMAKE_ROOT_DIR}/lib/x64)
endif()

add_library(${PROJECT_NAME} SHARED ${DIR_SRCS} ${PLATFORM_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC tinySFML_System)
if(SXB_OS_WINDOWS)
	target_link_libraries(${PROJECT_NAME} PRIVATE winmm gdi32)
endif()

if(SXB_OS_WINDOWS)
	INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_ROOT_DIR}/bin/win64/Debug)
else()
	INSTALL(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_ROOT_DIR}/bin/x64/Debug)
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "libs")

