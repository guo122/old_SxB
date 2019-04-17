include(CMakeParseArguments)
MESSAGE(STATUS "is build" ${CMAKE_BUILD_TYPE})
#if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	#set(OUTPATH_SUFFIX "/Debug")
#else()
	#set(OUTPATH_SUFFIX "/Release")
#endif()
set(OUTPATH_SUFFIX "/Debug")

if(SXB_OS_WINDOWS)
	set(BIN_PATH ${CMAKE_ROOT_DIR}/bin/win64)
	set(LIB_PATH ${CMAKE_ROOT_DIR}/lib/win64)
elseif(SXB_OS_MACOS)
	set(BIN_PATH ${CMAKE_ROOT_DIR}/bin/macos)
	set(LIB_PATH ${CMAKE_ROOT_DIR}/lib/macos)
elseif(SXB_OS_IOS)
	set(BIN_PATH ${CMAKE_ROOT_DIR}/bin/ios)
	set(LIB_PATH ${CMAKE_ROOT_DIR}/lib/ios)
else()
	set(BIN_PATH ${CMAKE_ROOT_DIR}/bin/unkown${OUTPATH_SUFFIX})
	set(LIB_PATH ${CMAKE_ROOT_DIR}/lib/unkown${OUTPATH_SUFFIX})
endif()

macro(sxb_add_library target)
    cmake_parse_arguments(THIS "SHARED;INSTALL" "" "FOLDER;SOURCES" ${ARGN})
	
	SET(LIBRARY_OUTPUT_PATH ${LIB_PATH})

	if (THIS_SHARED)
        add_library(${target} SHARED ${THIS_SOURCES})
    else()
        add_library(${target} ${THIS_SOURCES})
    endif()
	
	string(REPLACE "-" "_" NAME_UPPER "${target}")
    string(TOUPPER "${NAME_UPPER}" NAME_UPPER)
    set_target_properties(${target} PROPERTIES DEFINE_SYMBOL ${NAME_UPPER}_EXPORTS)

	if(SXB_OS_MACOS)
		set_property(TARGET ${target} PROPERTY XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
	endif()

	if (THIS_FOLDER)
		set_target_properties(${target} PROPERTIES FOLDER ${THIS_FOLDER})
	endif()
	
	if (THIS_INSTALL)
		if(SXB_OS_WINDOWS)
			INSTALL(TARGETS ${target} RUNTIME DESTINATION ${BIN_PATH}${OUTPATH_SUFFIX})
		else()
			INSTALL(TARGETS ${target} LIBRARY DESTINATION ${BIN_PATH})
		endif()
	endif()
endmacro()

macro(sxb_add_executable target)
    cmake_parse_arguments(THIS "" "" "FOLDER;SOURCES" ${ARGN})
	
	SET(EXECUTABLE_OUTPUT_PATH ${BIN_PATH})

	if(SXB_OS_IOS)
		set(BUNDLE_SRCS
			${CMAKE_ROOT_DIR}/ios/Assets.xcassets
			${CMAKE_ROOT_DIR}/ios/runtime.bundle
		)
		add_executable(${target} ${THIS_SOURCES} ${BUNDLE_SRCS})
		set_target_properties(
			${target}
    		PROPERTIES
    		MACOSX_BUNDLE YES 
			MACOSX_BUNDLE_INFO_PLIST "${CMAKE_ROOT_DIR}/ios/Info.plist"
    		RESOURCE "${BUNDLE_SRCS}"
		)
		set_target_properties(
			${target}
			PROPERTIES 
			XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon"
			XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_LAUNCHIMAGE_NAME "LaunchImage"
			XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
			XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1"
		)
	else()
		add_executable(${target} ${THIS_SOURCES})
	endif()

	if (THIS_FOLDER)
		set_target_properties(${target} PROPERTIES FOLDER ${THIS_FOLDER})
	endif()

endmacro()

function(sfml_add_external)
    list(GET ARGN 0 target)
    list(REMOVE_AT ARGN 0)

    if (TARGET ${target})
        message(FATAL_ERROR "Target '${target}' is already defined")
    endif()

    cmake_parse_arguments(THIS "" "" "INCLUDE;LINK" ${ARGN})
    if (THIS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown arguments when calling sfml_import_library: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    add_library(${target} INTERFACE)

    if (THIS_INCLUDE)
        foreach(include_dir IN LISTS THIS_INCLUDE)
            if (NOT include_dir)
                message(FATAL_ERROR "No path given for include dir ${THIS_INCLUDE}")
            endif()
            target_include_directories(${target} INTERFACE "$<BUILD_INTERFACE:${include_dir}>")
        endforeach()
    endif()

    if (THIS_LINK)
        foreach(link_item IN LISTS THIS_LINK)
            if (NOT link_item)
                message(FATAL_ERROR "Missing item in ${THIS_LINK}")
            endif()
            target_link_libraries(${target} INTERFACE "$<BUILD_INTERFACE:${link_item}>")
        endforeach()
    endif()

    install(TARGETS ${target} EXPORT SFMLConfigExport)
endfunction()

function(sfml_find_package)
    list(GET ARGN 0 target)
    list(REMOVE_AT ARGN 0)

    if (TARGET ${target})
        message(FATAL_ERROR "Target '${target}' is already defined")
    endif()

    cmake_parse_arguments(THIS "" "" "INCLUDE;LINK" ${ARGN})
    if (THIS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown arguments when calling sfml_import_library: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/")
    if (SFML_OS_IOS)
        find_host_package(${target} REQUIRED)
    else()
        find_package(${target} REQUIRED)
    endif()

    # Make sure to interpret the items in INCLUDE and LINK parameters. sfml_add_external()
    # does not interpret given items in order to also accept parameters that must not be interpreted
    set(LINK_LIST "")
    if (THIS_LINK)
        foreach(link_item IN LISTS THIS_LINK)
            list(APPEND LINK_LIST "${${link_item}}")
        endforeach()
    endif()

    set(INCLUDE_LIST "")
    if (THIS_INCLUDE)
        foreach(include_dir IN LISTS THIS_INCLUDE)
            list(APPEND INCLUDE_LIST "${${include_dir}}")
        endforeach()
    endif()

    sfml_add_external(${target} INCLUDE ${INCLUDE_LIST} LINK ${LINK_LIST})
endfunction()
