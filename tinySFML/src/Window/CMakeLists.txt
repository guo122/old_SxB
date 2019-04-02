
set(PROJECT_NAME tinySFML_Window)

set(DIR_SRCS ${CMAKE_ROOT_DIR}/tinySFML/include/Config.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/Window/Export.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/Window/WindowBase.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/WindowBase.cpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/Window/Cursor.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Cursor.cpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/CursorImpl.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/Window/VideoMode.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/VideoMode.cpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/VideoModeImpl.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/Window/WindowHandle.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/Window/WindowStyle.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/WindowImpl.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/WindowImpl.cpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/Window/ContextSettings.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/Window/Event.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/Window/Joystick.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Joystick.cpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/JoystickImpl.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/JoystickManager.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/JoystickManager.cpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/Window/Keyboard.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Keyboard.cpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/InputImpl.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/Window/Mouse.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Mouse.cpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/Window/Sensor.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Sensor.cpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/SensorImpl.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/SensorManager.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/Window/SensorManager.cpp
			 )
			 
# add platform specific sources
if(WIN32)
    set(PLATFORM_SRC
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Win32/CursorImpl.hpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Win32/CursorImpl.cpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Win32/VideoModeImpl.cpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Win32/JoystickImpl.hpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Win32/JoystickImpl.cpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Win32/InputImpl.hpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Win32/InputImpl.cpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Win32/SensorImpl.hpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Win32/SensorImpl.cpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Win32/WindowImplWin32.hpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Win32/WindowImplWin32.cpp
    )
    source_group("windows" FILES ${PLATFORM_SRC})
else()
    set(PLATFORM_SRC
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Unix/CursorImpl.hpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Unix/CursorImpl.cpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Unix/VideoModeImpl.cpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Unix/JoystickImpl.hpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Unix/JoystickImpl.cpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Unix/InputImpl.hpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Unix/InputImpl.cpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Unix/SensorImpl.hpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Unix/SensorImpl.cpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Unix/WindowImplX11.hpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/Window/Unix/WindowImplX11.cpp
    )

    source_group("unix" FILES ${PLATFORM_SRC})
endif()

set(DIR_SRCS ${DIR_SRCS} ${PLATFORM_SRC})

set(INC_DIR ${CMAKE_ROOT_DIR}/tinySFML/include
			${CMAKE_ROOT_DIR}/tinySFML/src
			)

include_directories(${INC_DIR})

#Add_Definitions(-D_HAS_ITERATOR_DEBUGGING=0)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_ROOT_DIR}/lib/x64)

add_library(${PROJECT_NAME} STATIC ${DIR_SRCS})
#add_library(${PROJECT_NAME} SHARED ${DIR_SRCS})

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "tinySFML")

