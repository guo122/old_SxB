
#ifndef TTSFML_SENSORIMPL_HPP
#define TTSFML_SENSORIMPL_HPP

#include <Config.hpp>
#include <Window/Sensor.hpp>

#if defined(SFML_SYSTEM_WINDOWS)

    #include <Window/Win32/SensorImpl.hpp>

#elif defined(SFML_SYSTEM_LINUX) || defined(SFML_SYSTEM_FREEBSD) || defined(SFML_SYSTEM_OPENBSD)

    #include <Window/Unix/SensorImpl.hpp>

#elif defined(SFML_SYSTEM_MACOS)

    #include <Window/OSX/SensorImpl.hpp>

#elif defined(SFML_SYSTEM_IOS)

    #include <Window/iOS/SensorImpl.hpp>

#elif defined(SFML_SYSTEM_ANDROID)

    #include <Window/Android/SensorImpl.hpp>

#endif


#endif // SFML_SENSORIMPL_HPP
