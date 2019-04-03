
set(PROJECT_NAME tinySFML_System)

set(DIR_SRCS ${CMAKE_ROOT_DIR}/tinySFML/include/Config.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/System/Export.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/System/NonCopyable.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/System/Vector2.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/System/Vector2.inl
			 ${CMAKE_ROOT_DIR}/tinySFML/include/System/Vector3.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/System/Vector3.inl
			 ${CMAKE_ROOT_DIR}/tinySFML/include/System/Time.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/System/Time.cpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/System/Clock.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/System/Clock.cpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/System/String.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/System/String.inl
			 ${CMAKE_ROOT_DIR}/tinySFML/src/System/String.cpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/System/Utf.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/System/Utf.inl
			 ${CMAKE_ROOT_DIR}/tinySFML/include/System/Mutex.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/System/Mutex.cpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/System/Lock.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/System/Lock.cpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/System/Err.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/System/Err.cpp
			 ${CMAKE_ROOT_DIR}/tinySFML/include/System/Sleep.hpp
			 ${CMAKE_ROOT_DIR}/tinySFML/src/System/Sleep.cpp
			 )

# add platform specific sources
if(WIN32)
    set(PLATFORM_SRC
        ${CMAKE_ROOT_DIR}/tinySFML/src/System/Win32/ClockImpl.hpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/System/Win32/ClockImpl.cpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/System/Win32/MutexImpl.hpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/System/Win32/MutexImpl.cpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/System/Win32/SleepImpl.hpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/System/Win32/SleepImpl.cpp
    )
    source_group("windows" FILES ${PLATFORM_SRC})
else()
    set(PLATFORM_SRC
        ${CMAKE_ROOT_DIR}/tinySFML/src/System/Unix/ClockImpl.hpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/System/Unix/ClockImpl.cpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/System/Unix/MutexImpl.hpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/System/Unix/MutexImpl.cpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/System/Unix/SleepImpl.hpp
        ${CMAKE_ROOT_DIR}/tinySFML/src/System/Unix/SleepImpl.cpp
    )

    source_group("unix" FILES ${PLATFORM_SRC})
endif()

set(DIR_SRCS ${DIR_SRCS} ${PLATFORM_SRC})
			 

set(INC_DIR ${CMAKE_ROOT_DIR}/tinySFML/include
			${CMAKE_ROOT_DIR}/tinySFML/src/
			)
			
set(LINK_LIB winmm)

include_directories(${INC_DIR})
#link_directories(${LINK_DIR})
link_libraries(${LINK_LIB})

#Add_Definitions(-D_HAS_ITERATOR_DEBUGGING=0)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_ROOT_DIR}/lib/x64)
#SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_ROOT_DIR}/bin/x64)

#add_library(${PROJECT_NAME} STATIC ${DIR_SRCS})
add_library(${PROJECT_NAME} SHARED ${DIR_SRCS})

INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_ROOT_DIR}/bin/x64/Debug)
#INSTALL(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_ROOT_DIR}/bin/x64)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "tinySFML")

