
#ifndef TTSFML_WINDOWIMPL_HPP
#define TTSFML_WINDOWIMPL_HPP

#include <Config.hpp>
#include <System/NonCopyable.hpp>
#include <System/String.hpp>
#include <Window/ContextSettings.hpp>
#include <Window/CursorImpl.hpp>
#include <Window/Event.hpp>
#include <Window/Joystick.hpp>
#include <Window/JoystickImpl.hpp>
#include <Window/Sensor.hpp>
#include <Window/SensorImpl.hpp>
#include <Window/VideoMode.hpp>
#include <Window/WindowHandle.hpp>
#include <Window/WindowBase.hpp>
#include <queue>
#include <set>

namespace tinySFML
{
class WindowListener;

namespace priv
{

class WindowImpl : NonCopyable
{
public:

    static WindowImpl* create(VideoMode mode, const String& title, Uint32 style, const ContextSettings& settings);

    static WindowImpl* create(WindowHandle handle);

public:

    virtual ~WindowImpl();

    void setJoystickThreshold(float threshold);

    bool popEvent(Event& event, bool block);

    virtual WindowHandle getSystemHandle() const = 0;

    virtual Vector2i getPosition() const = 0;

    virtual void setPosition(const Vector2i& position) = 0;

    virtual Vector2u getSize() const = 0;

    virtual void setSize(const Vector2u& size) = 0;

    virtual void setTitle(const String& title) = 0;

    virtual void setIcon(unsigned int width, unsigned int height, const Uint8* pixels) = 0;

    virtual void setVisible(bool visible) = 0;

    virtual void setMouseCursorVisible(bool visible) = 0;

    virtual void setMouseCursorGrabbed(bool grabbed) = 0;

    virtual void setMouseCursor(const CursorImpl& cursor) = 0;

    virtual void setKeyRepeatEnabled(bool enabled) = 0;

    virtual void requestFocus() = 0;

    virtual bool hasFocus() const = 0;

protected:

    WindowImpl();

    void pushEvent(const Event& event);

    virtual void processEvents() = 0;

private:

    void processJoystickEvents();

    void processSensorEvents();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::queue<Event> m_events;                                              ///< Queue of available events
    JoystickState     m_joystickStates[Joystick::Count];                     ///< Previous state of the joysticks
    Vector3f          m_sensorValue[Sensor::Count];                          ///< Previous value of the sensors
    float             m_joystickThreshold;                                   ///< Joystick threshold (minimum motion for "move" event to be generated)
    float             m_previousAxes[Joystick::Count][Joystick::AxisCount];  ///< Position of each axis last time a move event triggered, in range [-100, 100]
};

} // namespace priv

} // namespace tinySFML


#endif // SFML_WINDOWIMPL_HPP
