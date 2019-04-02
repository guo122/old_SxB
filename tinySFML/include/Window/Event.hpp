
#ifndef TTSFML_EVENT_HPP
#define TTSFML_EVENT_HPP

#include <Config.hpp>
#include <Window/Joystick.hpp>
#include <Window/Keyboard.hpp>
#include <Window/Mouse.hpp>
#include <Window/Sensor.hpp>


namespace ttsf
{

class Event
{
public:

    struct SizeEvent
    {
        unsigned int width;  ///< New width, in pixels
        unsigned int height; ///< New height, in pixels
    };

    struct KeyEvent
    {
        Keyboard::Key code;    ///< Code of the key that has been pressed
        bool          alt;     ///< Is the Alt key pressed?
        bool          control; ///< Is the Control key pressed?
        bool          shift;   ///< Is the Shift key pressed?
        bool          system;  ///< Is the System key pressed?
    };

    struct TextEvent
    {
        Uint32 unicode; ///< UTF-32 Unicode value of the character
    };

    struct MouseMoveEvent
    {
        int x; ///< X position of the mouse pointer, relative to the left of the owner window
        int y; ///< Y position of the mouse pointer, relative to the top of the owner window
    };

    struct MouseButtonEvent
    {
        Mouse::Button button; ///< Code of the button that has been pressed
        int           x;      ///< X position of the mouse pointer, relative to the left of the owner window
        int           y;      ///< Y position of the mouse pointer, relative to the top of the owner window
    };

    struct MouseWheelEvent
    {
        int delta; ///< Number of ticks the wheel has moved (positive is up, negative is down)
        int x;     ///< X position of the mouse pointer, relative to the left of the owner window
        int y;     ///< Y position of the mouse pointer, relative to the top of the owner window
    };

    struct MouseWheelScrollEvent
    {
        Mouse::Wheel wheel; ///< Which wheel (for mice with multiple ones)
        float        delta; ///< Wheel offset (positive is up/left, negative is down/right). High-precision mice may use non-integral offsets.
        int          x;     ///< X position of the mouse pointer, relative to the left of the owner window
        int          y;     ///< Y position of the mouse pointer, relative to the top of the owner window
    };

    struct JoystickConnectEvent
    {
        unsigned int joystickId; ///< Index of the joystick (in range [0 .. Joystick::Count - 1])
    };

    struct JoystickMoveEvent
    {
        unsigned int   joystickId; ///< Index of the joystick (in range [0 .. Joystick::Count - 1])
        Joystick::Axis axis;       ///< Axis on which the joystick moved
        float          position;   ///< New position on the axis (in range [-100 .. 100])
    };

    struct JoystickButtonEvent
    {
        unsigned int joystickId; ///< Index of the joystick (in range [0 .. Joystick::Count - 1])
        unsigned int button;     ///< Index of the button that has been pressed (in range [0 .. Joystick::ButtonCount - 1])
    };

    struct TouchEvent
    {
        unsigned int finger; ///< Index of the finger in case of multi-touch events
        int x;               ///< X position of the touch, relative to the left of the owner window
        int y;               ///< Y position of the touch, relative to the top of the owner window
    };

    struct SensorEvent
    {
        Sensor::Type type; ///< Type of the sensor
        float x;           ///< Current value of the sensor on X axis
        float y;           ///< Current value of the sensor on Y axis
        float z;           ///< Current value of the sensor on Z axis
    };

    enum EventType
    {
        Closed,                 ///< The window requested to be closed (no data)
        Resized,                ///< The window was resized (data in event.size)
        LostFocus,              ///< The window lost the focus (no data)
        GainedFocus,            ///< The window gained the focus (no data)
        TextEntered,            ///< A character was entered (data in event.text)
        KeyPressed,             ///< A key was pressed (data in event.key)
        KeyReleased,            ///< A key was released (data in event.key)
        MouseWheelMoved,        ///< The mouse wheel was scrolled (data in event.mouseWheel) (deprecated)
        MouseWheelScrolled,     ///< The mouse wheel was scrolled (data in event.mouseWheelScroll)
        MouseButtonPressed,     ///< A mouse button was pressed (data in event.mouseButton)
        MouseButtonReleased,    ///< A mouse button was released (data in event.mouseButton)
        MouseMoved,             ///< The mouse cursor moved (data in event.mouseMove)
        MouseEntered,           ///< The mouse cursor entered the area of the window (no data)
        MouseLeft,              ///< The mouse cursor left the area of the window (no data)
        JoystickButtonPressed,  ///< A joystick button was pressed (data in event.joystickButton)
        JoystickButtonReleased, ///< A joystick button was released (data in event.joystickButton)
        JoystickMoved,          ///< The joystick moved along an axis (data in event.joystickMove)
        JoystickConnected,      ///< A joystick was connected (data in event.joystickConnect)
        JoystickDisconnected,   ///< A joystick was disconnected (data in event.joystickConnect)
        TouchBegan,             ///< A touch event began (data in event.touch)
        TouchMoved,             ///< A touch moved (data in event.touch)
        TouchEnded,             ///< A touch event ended (data in event.touch)
        SensorChanged,          ///< A sensor value changed (data in event.sensor)

        Count                   ///< Keep last -- the total number of event types
    };

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    EventType type; ///< Type of the event

    union
    {
        SizeEvent             size;              ///< Size event parameters (Event::Resized)
        KeyEvent              key;               ///< Key event parameters (Event::KeyPressed, Event::KeyReleased)
        TextEvent             text;              ///< Text event parameters (Event::TextEntered)
        MouseMoveEvent        mouseMove;         ///< Mouse move event parameters (Event::MouseMoved)
        MouseButtonEvent      mouseButton;       ///< Mouse button event parameters (Event::MouseButtonPressed, Event::MouseButtonReleased)
        MouseWheelEvent       mouseWheel;        ///< Mouse wheel event parameters (Event::MouseWheelMoved) (deprecated)
        MouseWheelScrollEvent mouseWheelScroll;  ///< Mouse wheel event parameters (Event::MouseWheelScrolled)
        JoystickMoveEvent     joystickMove;      ///< Joystick move event parameters (Event::JoystickMoved)
        JoystickButtonEvent   joystickButton;    ///< Joystick button event parameters (Event::JoystickButtonPressed, Event::JoystickButtonReleased)
        JoystickConnectEvent  joystickConnect;   ///< Joystick (dis)connect event parameters (Event::JoystickConnected, Event::JoystickDisconnected)
        TouchEvent            touch;             ///< Touch events parameters (Event::TouchBegan, Event::TouchMoved, Event::TouchEnded)
        SensorEvent           sensor;            ///< Sensor event parameters (Event::SensorChanged)
    };
};

} // namespace sf


#endif // SFML_EVENT_HPP
