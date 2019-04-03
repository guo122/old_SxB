
#ifndef TTSFML_JOYSTICKIMPL_HPP
#define TTSFML_JOYSTICKIMPL_HPP

#include <Config.hpp>
#include <Window/Joystick.hpp>
#include <System/String.hpp>
#include <algorithm>

namespace tinySFML
{
namespace priv
{

struct JoystickCaps
{
    JoystickCaps()
    {
        buttonCount = 0;
        std::fill(axes, axes + Joystick::AxisCount, false);
    }

    unsigned int buttonCount;               ///< Number of buttons supported by the joystick
    bool         axes[Joystick::AxisCount]; ///< Support for each axis
};

struct JoystickState
{
    JoystickState()
    {
        connected = false;
        std::fill(axes, axes + Joystick::AxisCount, 0.f);
        std::fill(buttons, buttons + Joystick::ButtonCount, false);
    }

    bool  connected;                      ///< Is the joystick currently connected?
    float axes[Joystick::AxisCount];      ///< Position of each axis, in range [-100, 100]
    bool  buttons[Joystick::ButtonCount]; ///< Status of each button (true = pressed)
};

} // namespace priv

} // namespace tinySFML


#if defined(SFML_SYSTEM_WINDOWS)

    #include <Window/Win32/JoystickImpl.hpp>

#elif defined(SFML_SYSTEM_LINUX)

    #include <SFML/Window/Unix/JoystickImpl.hpp>

#elif defined(SFML_SYSTEM_FREEBSD)

    #include <SFML/Window/FreeBSD/JoystickImpl.hpp>

#elif defined(SFML_SYSTEM_OPENBSD)

    #include <SFML/Window/OpenBSD/JoystickImpl.hpp>

#elif defined(SFML_SYSTEM_MACOS)

    #include <SFML/Window/OSX/JoystickImpl.hpp>

#elif defined(SFML_SYSTEM_IOS)

    #include <SFML/Window/iOS/JoystickImpl.hpp>

#elif defined(SFML_SYSTEM_ANDROID)

    #include <SFML/Window/Android/JoystickImpl.hpp>

#endif


#endif // SFML_JOYSTICKIMPL_HPP
