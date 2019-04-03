
#ifndef TTSFML_JOYSTICKMANAGER_HPP
#define TTSFML_JOYSTICKMANAGER_HPP

#include <Window/Joystick.hpp>
#include <Window/JoystickImpl.hpp>
#include <System/NonCopyable.hpp>

namespace tinySFML
{
namespace priv
{

class JoystickManager : NonCopyable
{
public:
    static JoystickManager& getInstance();

    const JoystickCaps& getCapabilities(unsigned int joystick) const;

    const JoystickState& getState(unsigned int joystick) const;

    const Joystick::Identification& getIdentification(unsigned int joystick) const;

    void update();

private:

    JoystickManager();

    ~JoystickManager();

    struct Item
    {
        JoystickImpl             joystick;       ///< Joystick implementation
        JoystickState            state;          ///< The current joystick state
        JoystickCaps             capabilities;   ///< The joystick capabilities
        Joystick::Identification identification; ///< The joystick identification
    };

    Item m_joysticks[Joystick::Count]; ///< Joysticks information and state
};

} // namespace priv

} // namespace tinySFML


#endif // SFML_JOYSTICKMANAGER_HPP
