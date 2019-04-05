
set(PROJECT_NAME tinySFML_System)

set(INCROOT ${CMAKE_ROOT_DIR}/tinySFML/include/System)
set(SRCROOT ${CMAKE_ROOT_DIR}/tinySFML/src/System)

set(DIR_SRCS 
	${CMAKE_ROOT_DIR}/tinySFML/include/Config.hpp
	${INCROOT}/Export.hpp
	${INCROOT}/NonCopyable.hpp
	${INCROOT}/Vector2.hpp
	${INCROOT}/Vector2.inl
	${INCROOT}/Vector3.hpp
	${INCROOT}/Vector3.inl
	${INCROOT}/Time.hpp
	${SRCROOT}/Time.cpp
	${INCROOT}/Clock.hpp
	${SRCROOT}/Clock.cpp
	${INCROOT}/String.hpp
	${INCROOT}/String.inl
	${SRCROOT}/String.cpp
	${INCROOT}/Utf.hpp
	${INCROOT}/Utf.inl
	${INCROOT}/Mutex.hpp
	${SRCROOT}/Mutex.cpp
	${INCROOT}/Lock.hpp
	${SRCROOT}/Lock.cpp
	${INCROOT}/Err.hpp
	${SRCROOT}/Err.cpp
	${INCROOT}/Sleep.hpp
	${SRCROOT}/Sleep.cpp
)

# add platform specific sources
if(SXB_OS_WINDOWS)
    set(PLATFORM_SRC
        ${SRCROOT}/Win32/ClockImpl.hpp
        ${SRCROOT}/Win32/ClockImpl.cpp
        ${SRCROOT}/Win32/MutexImpl.hpp
        ${SRCROOT}/Win32/MutexImpl.cpp
        ${SRCROOT}/Win32/SleepImpl.hpp
        ${SRCROOT}/Win32/SleepImpl.cpp
    )
    source_group("windows" FILES ${PLATFORM_SRC})
else()
    set(PLATFORM_SRC
        ${SRCROOT}/Unix/ClockImpl.hpp
        ${SRCROOT}/Unix/ClockImpl.cpp
        ${SRCROOT}/Unix/MutexImpl.hpp
        ${SRCROOT}/Unix/MutexImpl.cpp
        ${SRCROOT}/Unix/SleepImpl.hpp
        ${SRCROOT}/Unix/SleepImpl.cpp
    )
	
	if(SXB_OS_ANDROID)
        set(PLATFORM_SRC ${PLATFORM_SRC}
            ${SRCROOT}/Android/Activity.hpp
            ${SRCROOT}/Android/Activity.cpp
            ${SRCROOT}/Android/NativeActivity.cpp
            ${SRCROOT}/Android/ResourceStream.cpp
            ${SRCROOT}/Android/ResourceStream.cpp
        )
    endif()
    source_group("unix" FILES ${PLATFORM_SRC})
endif()
			 
set(INC_DIR 
	${CMAKE_ROOT_DIR}/tinySFML/include
	${CMAKE_ROOT_DIR}/tinySFML/src/
)	
include_directories(${INC_DIR})

if(SXB_OS_WINDOWS)
	SET(LIBRARY_OUTPUT_PATH ${CMAKE_ROOT_DIR}/lib/win64)
else()
	SET(LIBRARY_OUTPUT_PATH ${CMAKE_ROOT_DIR}/lib/x64)
endif()

add_library(${PROJECT_NAME} SHARED ${DIR_SRCS} ${PLATFORM_SRC})

if(SXB_OS_WINDOWS)
	target_link_libraries(${PROJECT_NAME} PRIVATE winmm)
endif()

if(SXB_OS_WINDOWS)
	INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_ROOT_DIR}/bin/win64/Debug)
else()
	INSTALL(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_ROOT_DIR}/bin/x64/Debug)
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "libs")

