
#ifndef TTSFML_JOYSTICK_HPP
#define TTSFML_JOYSTICK_HPP

#include <Window/Export.hpp>
#include <System/String.hpp>

namespace ttsf
{
class TTSFML_WINDOW_API Joystick
{
public:

    enum
    {
        Count       = 8,  ///< Maximum number of supported joysticks
        ButtonCount = 32, ///< Maximum number of supported buttons
        AxisCount   = 8   ///< Maximum number of supported axes
    };

    enum Axis
    {
        X,    ///< The X axis
        Y,    ///< The Y axis
        Z,    ///< The Z axis
        R,    ///< The R axis
        U,    ///< The U axis
        V,    ///< The V axis
        PovX, ///< The X axis of the point-of-view hat
        PovY  ///< The Y axis of the point-of-view hat
    };

    struct TTSFML_WINDOW_API Identification
    {
        Identification();

        String       name;      ///< Name of the joystick
        unsigned int vendorId;  ///< Manufacturer identifier
        unsigned int productId; ///< Product identifier
    };

    static bool isConnected(unsigned int joystick);

    static unsigned int getButtonCount(unsigned int joystick);

    static bool hasAxis(unsigned int joystick, Axis axis);

    static bool isButtonPressed(unsigned int joystick, unsigned int button);

    static float getAxisPosition(unsigned int joystick, Axis axis);

    static Identification getIdentification(unsigned int joystick);

    static void update();
};

} // namespace sf


#endif // SFML_JOYSTICK_HPP
