
#ifndef TTSFML_INPUTIMPLWIN32_HPP
#define TTSFML_INPUTIMPLWIN32_HPP

#include <Window/Keyboard.hpp>
#include <Window/Mouse.hpp>


namespace tinySFML
{
namespace priv
{

class InputImpl
{
public:

    static bool isKeyPressed(Keyboard::Key key);

    static void setVirtualKeyboardVisible(bool visible);

    static bool isMouseButtonPressed(Mouse::Button button);

    static Vector2i getMousePosition();

    static Vector2i getMousePosition(const WindowBase& relativeTo);

    static void setMousePosition(const Vector2i& position);

    static void setMousePosition(const Vector2i& position, const WindowBase& relativeTo);

    static bool isTouchDown(unsigned int finger);

    static Vector2i getTouchPosition(unsigned int finger);

    static Vector2i getTouchPosition(unsigned int finger, const WindowBase& relativeTo);
};

} // namespace priv

} // namespace tinySFML


#endif // SFML_INPUTIMPLWIN32_HPP
