
#ifndef TTSFML_CURSOR_HPP
#define TTSFML_CURSOR_HPP

#include <Window/Export.hpp>
#include <System/NonCopyable.hpp>
#include <System/Vector2.hpp>

namespace ttsf
{
namespace priv
{
    class CursorImpl;
}

class TTSFML_WINDOW_API Cursor : NonCopyable
{
public:
    enum Type
    {
        Arrow,                  ///< Arrow cursor (default)
        ArrowWait,              ///< Busy arrow cursor
        Wait,                   ///< Busy cursor
        Text,                   ///< I-beam, cursor when hovering over a field allowing text entry
        Hand,                   ///< Pointing hand cursor
        SizeHorizontal,         ///< Horizontal double arrow cursor
        SizeVertical,           ///< Vertical double arrow cursor
        SizeTopLeftBottomRight, ///< Double arrow cursor going from top-left to bottom-right
        SizeBottomLeftTopRight, ///< Double arrow cursor going from bottom-left to top-right
        SizeAll,                ///< Combination of SizeHorizontal and SizeVertical
        Cross,                  ///< Crosshair cursor
        Help,                   ///< Help cursor
        NotAllowed              ///< Action not allowed cursor
    };

public:

    Cursor();

    ~Cursor();

    bool loadFromPixels(const Uint8* pixels, Vector2u size, Vector2u hotspot);

    bool loadFromSystem(Type type);

private:

    friend class WindowBase;

    const priv::CursorImpl& getImpl() const;

private:

    priv::CursorImpl* m_impl; ///< Platform-specific implementation of the cursor
};

} // namespace sf


#endif // SFML_CURSOR_HPP
