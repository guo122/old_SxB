
#ifndef TTSFML_WINDOWBASE_HPP
#define TTSFML_WINDOWBASE_HPP

#include <Window/Cursor.hpp>
#include <Window/Export.hpp>

#include <System/NonCopyable.hpp>
#include <System/Vector2.hpp>

#include <Window/VideoMode.hpp>
#include <Window/WindowHandle.hpp>
#include <Window/WindowStyle.hpp>
#include <System/Clock.hpp>
#include <System/String.hpp>

namespace ttsf
{
namespace priv
{
    class WindowImpl;
}

class Event;

class TTSFML_WINDOW_API WindowBase : NonCopyable
{
public:
    WindowBase();

    WindowBase(VideoMode mode, const String& title, Uint32 style = Style::Default);

    explicit WindowBase(WindowHandle handle);

    virtual ~WindowBase();

    virtual void create(VideoMode mode, const String& title, Uint32 style = Style::Default);

    virtual void create(WindowHandle handle);

    virtual void close();

    bool isOpen() const;

    bool pollEvent(Event& event);

    bool waitEvent(Event& event);

    Vector2i getPosition() const;

    void setPosition(const Vector2i& position);

    Vector2u getSize() const;

    void setSize(const Vector2u& size);

    void setTitle(const String& title);

    void setIcon(unsigned int width, unsigned int height, const Uint8* pixels);

    void setVisible(bool visible);

    void setMouseCursorVisible(bool visible);

    void setMouseCursorGrabbed(bool grabbed);

    void setMouseCursor(const Cursor& cursor);

    void setKeyRepeatEnabled(bool enabled);

    void setJoystickThreshold(float threshold);

    void requestFocus();

    bool hasFocus() const;

    WindowHandle getSystemHandle() const;

protected:

    virtual void onCreate();

    virtual void onResize();

private:

    friend class Window;

    bool filterEvent(const Event& event);

    void initialize();

    const WindowBase* getFullscreenWindow();

    void setFullscreenWindow(const WindowBase* window);

    priv::WindowImpl* m_impl;           ///< Platform-specific implementation of the window
    Vector2u          m_size;           ///< Current size of the window
};

} // namespace sf


#endif // SFML_WINDOWBASE_HPP