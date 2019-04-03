
#ifndef TTSFML_WINDOWHANDLE_HPP
#define TTSFML_WINDOWHANDLE_HPP

#include <Config.hpp>

// Windows' HWND is a typedef on struct HWND__*
#if defined(SFML_SYSTEM_WINDOWS)
    struct HWND__;
#endif

namespace tinySFML
{
#if defined(SFML_SYSTEM_WINDOWS)

    // Window handle is HWND (HWND__*) on Windows
    typedef HWND__* WindowHandle;

#elif defined(SFML_SYSTEM_LINUX) || defined(SFML_SYSTEM_FREEBSD) || defined(SFML_SYSTEM_OPENBSD)

    // Window handle is Window (unsigned long) on Unix - X11
    typedef unsigned long WindowHandle;

#elif defined(SFML_SYSTEM_MACOS)

    // Window handle is NSWindow or NSView (void*) on Mac OS X - Cocoa
    typedef void* WindowHandle;

#elif defined(SFML_SYSTEM_IOS)

    // Window handle is UIWindow (void*) on iOS - UIKit
    typedef void* WindowHandle;

#elif defined(SFML_SYSTEM_ANDROID)

    // Window handle is ANativeWindow* (void*) on Android
    typedef void* WindowHandle;

#elif defined(SFML_DOXYGEN)

    // Define typedef symbol so that Doxygen can attach some documentation to it
    typedef "platform-specific" WindowHandle;

#endif

} // namespace tinySFML


#endif // SFML_WINDOWHANDLE_HPP