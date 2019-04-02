
#ifndef TTSFML_INPUTIMPL_HPP
#define TTSFML_INPUTIMPL_HPP

#include <Config.hpp>

#if defined(SFML_SYSTEM_WINDOWS)
    #include <Window/Win32/InputImpl.hpp>
#elif defined(SFML_SYSTEM_LINUX) || defined(SFML_SYSTEM_FREEBSD) || defined(SFML_SYSTEM_OPENBSD)
    #include <SFML/Window/Unix/InputImpl.hpp>
#elif defined(SFML_SYSTEM_MACOS)
    #include <SFML/Window/OSX/InputImpl.hpp>
#elif defined(SFML_SYSTEM_IOS)
    #include <SFML/Window/iOS/InputImpl.hpp>
#elif defined(SFML_SYSTEM_ANDROID)
    #include <SFML/Window/Android/InputImpl.hpp>
#endif


#endif // SFML_INPUTIMPL_HPP
