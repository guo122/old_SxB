
MESSAGE(STATUS "operation system is" ${CMAKE_SYSTEM_NAME})
if(WIN32)
	set(SXB_OS_WINDOWS 1)
elseif(APPLE)
	set(SXB_OS_MACOS 1)
elseif(UNIX)
	set(SXB_OS_UNIX 1)
	message(WARNING "UNIX has not been adapted yet.")
else()
	message(FATAL_ERROR "Unsupported operating system or environment")
	return()
endif()

