
#ifndef CONFIG_H_839C346C6E9225385C6EF458D3A2F1C3
#define CONFIG_H_839C346C6E9225385C6EF458D3A2F1C3

////////////////////////////////////////////////////////////
// Identify the operating system
// see http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
////////////////////////////////////////////////////////////
#if defined(_WIN32)

// Windows
#define SXB_SYSTEM_WINDOWS
#ifndef NOMINMAX
#define NOMINMAX
#endif

#elif defined(__APPLE__) && defined(__MACH__)

// Apple platform, see which one it is
#include "TargetConditionals.h"

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

// iOS
#define SXB_SYSTEM_IOS

#elif TARGET_OS_MAC

// MacOS
#define SXB_SYSTEM_MACOS

#else

// Unsupported Apple system
#error This Apple operating system is not supported by SXB library

#endif

#elif defined(__unix__)

// UNIX system, see which one it is
#if defined(__ANDROID__)

// Android
#define SXB_SYSTEM_ANDROID

#elif defined(__linux__)

// Linux
#define SXB_SYSTEM_LINUX

#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

// FreeBSD
#define SXB_SYSTEM_FREEBSD

#elif defined(__OpenBSD__)

// OpenBSD
#define SXB_SYSTEM_OPENBSD

#else

// Unsupported UNIX system
#error This UNIX operating system is not supported by SXB library

#endif

#else

// Unsupported system
#error This operating system is not supported by SXB library

#endif


////////////////////////////////////////////////////////////
// Define a portable debug macro
////////////////////////////////////////////////////////////
#if !defined(NDEBUG)

#define SXB_DEBUG

#endif

#endif // CONFIG_H_839C346C6E9225385C6EF458D3A2F1C3
