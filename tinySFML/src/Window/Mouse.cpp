
#include <Window/Mouse.hpp>
#include <Window/InputImpl.hpp>
#include <Window/WindowBase.hpp>

namespace ttsf
{
////////////////////////////////////////////////////////////
bool Mouse::isButtonPressed(Button button)
{
    return priv::InputImpl::isMouseButtonPressed(button);
}


////////////////////////////////////////////////////////////
Vector2i Mouse::getPosition()
{
    return priv::InputImpl::getMousePosition();
}


////////////////////////////////////////////////////////////
Vector2i Mouse::getPosition(const WindowBase& relativeTo)
{
    return priv::InputImpl::getMousePosition(relativeTo);
}


////////////////////////////////////////////////////////////
void Mouse::setPosition(const Vector2i& position)
{
    priv::InputImpl::setMousePosition(position);
}


////////////////////////////////////////////////////////////
void Mouse::setPosition(const Vector2i& position, const WindowBase& relativeTo)
{
    priv::InputImpl::setMousePosition(position, relativeTo);
}

} // namespace sf
