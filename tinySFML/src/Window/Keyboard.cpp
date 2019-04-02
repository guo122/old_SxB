
#include <Window/Keyboard.hpp>
#include <Window/InputImpl.hpp>


namespace sf
{
////////////////////////////////////////////////////////////
bool Keyboard::isKeyPressed(Key key)
{
    return priv::InputImpl::isKeyPressed(key);
}


////////////////////////////////////////////////////////////
void Keyboard::setVirtualKeyboardVisible(bool visible)
{
    priv::InputImpl::setVirtualKeyboardVisible(visible);
}

} // namespace sf
