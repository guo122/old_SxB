
#ifndef TTSFML_CURSORIMPLWIN32_HPP
#define TTSFML_CURSORIMPLWIN32_HPP

#include <Window/Cursor.hpp>
#include <System/NonCopyable.hpp>
#include <System/Vector2.hpp>

#include <windows.h>

namespace ttsf
{

namespace priv
{

class CursorImpl : NonCopyable
{
public:

    CursorImpl();

    ~CursorImpl();

    bool loadFromPixels(const Uint8* pixels, Vector2u size, Vector2u hotspot);

    bool loadFromSystem(Cursor::Type type);

private:

    friend class WindowImplWin32;

    void release();

    HCURSOR m_cursor;
};

} // namespace priv

} // namespace sf

#endif // SFML_CUSROSIMPLWIN32_HPP

