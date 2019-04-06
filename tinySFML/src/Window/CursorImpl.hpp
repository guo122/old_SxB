
#ifndef TTSFML_CURSORIMPL_HPP
#define TTSFML_CURSORIMPL_HPP

#include <Config.hpp>

#if defined(SFML_SYSTEM_WINDOWS)

    #include <Window/Win32/CursorImpl.hpp>

#elif defined(SFML_SYSTEM_LINUX) || defined(SFML_SYSTEM_FREEBSD) || defined(SFML_SYSTEM_OPENBSD)

    #include <SFML/Window/Unix/CursorImpl.hpp>

#elif defined(SFML_SYSTEM_MACOS)

    #include <Window/OSX/CursorImpl.hpp>

#elif defined(SFML_SYSTEM_IOS)

    #include <SFML/Window/iOS/CursorImpl.hpp>

#elif defined(SFML_SYSTEM_ANDROID)

    #include <SFML/Window/Android/CursorImpl.hpp>

#endif


#endif // SFML_CURSORIMPL_HPP
