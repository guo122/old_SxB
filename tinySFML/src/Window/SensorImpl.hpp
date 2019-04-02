
#ifndef TTSFML_SENSORIMPL_HPP
#define TTSFML_SENSORIMPL_HPP

#include <Config.hpp>
#include <Window/Sensor.hpp>

#if defined(SFML_SYSTEM_WINDOWS)

    #include <Window/Win32/SensorImpl.hpp>

#elif defined(SFML_SYSTEM_LINUX) || defined(SFML_SYSTEM_FREEBSD) || defined(SFML_SYSTEM_OPENBSD)

    #include <SFML/Window/Unix/SensorImpl.hpp>

#elif defined(SFML_SYSTEM_MACOS)

    #include <SFML/Window/OSX/SensorImpl.hpp>

#elif defined(SFML_SYSTEM_IOS)

    #include <SFML/Window/iOS/SensorImpl.hpp>

#elif defined(SFML_SYSTEM_ANDROID)

    #include <SFML/Window/Android/SensorImpl.hpp>

#endif


#endif // SFML_SENSORIMPL_HPP
