
#ifndef TTSFML_INPUTIMPL_HPP
#define TTSFML_INPUTIMPL_HPP

#include <Config.hpp>

#if defined(SFML_SYSTEM_WINDOWS)
    #include <Window/Win32/InputImpl.hpp>
#elif defined(SFML_SYSTEM_LINUX) || defined(SFML_SYSTEM_FREEBSD) || defined(SFML_SYSTEM_OPENBSD)
    #include <Window/Unix/InputImpl.hpp>
#elif defined(SFML_SYSTEM_MACOS)
    #include <Window/OSX/InputImpl.hpp>
#elif defined(SFML_SYSTEM_IOS)
    #include <Window/iOS/InputImpl.hpp>
#elif defined(SFML_SYSTEM_ANDROID)
    #include <Window/Android/InputImpl.hpp>
#endif


#endif // SFML_INPUTIMPL_HPP
