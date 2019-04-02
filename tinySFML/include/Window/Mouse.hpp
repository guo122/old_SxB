
#ifndef TTSFML_MOUSE_HPP
#define TTSFML_MOUSE_HPP

#include <Window/Export.hpp>
#include <System/Vector2.hpp>

namespace ttsf
{
class WindowBase;

class TTSFML_WINDOW_API Mouse
{
public:

    enum Button
    {
        Left,       ///< The left mouse button
        Right,      ///< The right mouse button
        Middle,     ///< The middle (wheel) mouse button
        XButton1,   ///< The first extra mouse button
        XButton2,   ///< The second extra mouse button

        ButtonCount ///< Keep last -- the total number of mouse buttons
    };

    enum Wheel
    {
        VerticalWheel,  ///< The vertical mouse wheel
        HorizontalWheel ///< The horizontal mouse wheel
    };

    static bool isButtonPressed(Button button);

    static Vector2i getPosition();

    static Vector2i getPosition(const WindowBase& relativeTo);

    static void setPosition(const Vector2i& position);

    static void setPosition(const Vector2i& position, const WindowBase& relativeTo);
};

} // namespace sf


#endif // SFML_MOUSE_HPP
