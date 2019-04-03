
#ifndef TTSFML_WINDOWIMPLWIN32_HPP
#define TTSFML_WINDOWIMPLWIN32_HPP

#include <Window/Event.hpp>
#include <Window/WindowImpl.hpp>
#include <System/String.hpp>
#include <windows.h>


namespace tinySFML
{
namespace priv
{

class WindowImplWin32 : public WindowImpl
{
public:

    WindowImplWin32(WindowHandle handle);

    WindowImplWin32(VideoMode mode, const String& title, Uint32 style, const ContextSettings& settings);

    ~WindowImplWin32();

    virtual WindowHandle getSystemHandle() const;

    virtual Vector2i getPosition() const;

    virtual void setPosition(const Vector2i& position);

    virtual Vector2u getSize() const;

    virtual void setSize(const Vector2u& size);

    virtual void setTitle(const String& title);

    virtual void setIcon(unsigned int width, unsigned int height, const Uint8* pixels);

    virtual void setVisible(bool visible);

    virtual void setMouseCursorVisible(bool visible);

    virtual void setMouseCursorGrabbed(bool grabbed);

    virtual void setMouseCursor(const CursorImpl& cursor);

    virtual void setKeyRepeatEnabled(bool enabled);

    virtual void requestFocus();

    virtual bool hasFocus() const;

protected:

    virtual void processEvents();

private:

    void registerWindowClass();

    void switchToFullscreen(const VideoMode& mode);

    void cleanup();

    void processEvent(UINT message, WPARAM wParam, LPARAM lParam);

    void setTracking(bool track);

    void grabCursor(bool grabbed);

    static Keyboard::Key virtualKeyCodeToSF(WPARAM key, LPARAM flags);

    static LRESULT CALLBACK globalOnEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    HWND     m_handle;           ///< Win32 handle of the window
    LONG_PTR m_callback;         ///< Stores the original event callback function of the control
    bool     m_cursorVisible;    ///< Is the cursor visible or hidden?
    HCURSOR  m_lastCursor;       ///< Last cursor used -- this data is not owned by the window and is required to be always valid
    HICON    m_icon;             ///< Custom icon assigned to the window
    bool     m_keyRepeatEnabled; ///< Automatic key-repeat state for keydown events
    Vector2u m_lastSize;         ///< The last handled size of the window
    bool     m_resizing;         ///< Is the window being resized?
    Uint16   m_surrogate;        ///< First half of the surrogate pair, in case we're receiving a Unicode character in two events
    bool     m_mouseInside;      ///< Mouse is inside the window?
    bool     m_fullscreen;       ///< Is the window fullscreen?
    bool     m_cursorGrabbed;    ///< Is the mouse cursor trapped?
};

} // namespace priv

} // namespace tinySFML

#endif // SFML_WINDOWIMPLWIN32_HPP
