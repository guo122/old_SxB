
set(PROJECT_NAME sfml-main)

set(INCROOT ${CMAKE_ROOT_DIR}/include/SFML/Main)
set(SRCROOT ${CMAKE_ROOT_DIR}/src/SFML/Main)
# sources
if(SXB_OS_WINDOWS)
    set(SRC ${SRC} ${SRCROOT}/MainWin32.cpp)
elseif(SXB_OS_IOS)
    set(SRC ${SRC} ${SRCROOT}/MainiOS.mm)
elseif(SXB_OS_ANDROID)
    set(SRC ${SRC} ${SRCROOT}/MainAndroid.cpp)
else()
    return()
endif()

# define the sfml-main target
sxb_add_library(
                ${PROJECT_NAME}
                FOLDER "libs"
				SOURCES ${SRC}
)

# overwrite sfml-main suffix for backward compatibility with FindSFML.cmake
#set_target_properties(sfml-main PROPERTIES
#DEBUG_POSTFIX -d
#RELEASE_POSTFIX ""
#MINSIZEREL_POSTFIX ""
#RELWITHDEBINFO_POSTFIX "")

# because of a current limitation on Android (which prevents one library
# from depending on shared libraries), we need a boostrap activity which
# will load our shared libraries manually
if(SXB_OS_ANDROID)
    sfml_add_library(sfml-activity SOURCES ${SRCROOT}/SFMLActivity.cpp)
endif()
