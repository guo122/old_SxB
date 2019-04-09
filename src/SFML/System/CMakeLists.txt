
set(PROJECT_NAME sfml-system)

set(INCROOT ${CMAKE_ROOT_DIR}/include/SFML/System)
set(SRCROOT ${CMAKE_ROOT_DIR}/src/SFML/System)

set(DIR_SRCS 
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
			${INCROOT}/ThreadLocal.hpp
			${SRCROOT}/ThreadLocal.cpp
			${INCROOT}/ThreadLocalPtr.hpp
			${INCROOT}/ThreadLocalPtr.inl
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
        ${SRCROOT}/Unix/ThreadLocalImpl.hpp
        ${SRCROOT}/Unix/ThreadLocalImpl.cpp
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
	${CMAKE_ROOT_DIR}/src
)

include_directories(${INC_DIR})

sxb_add_library(
				${PROJECT_NAME} 
				SHARED INSTALL 
				FOLDER "libs" 
				SOURCES ${DIR_SRCS} ${PLATFORM_SRC}
)

if(SXB_OS_WINDOWS)
	target_link_libraries(${PROJECT_NAME} PRIVATE winmm)
endif()

