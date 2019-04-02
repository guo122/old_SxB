
#ifndef TTSFML_JOYSTICKIMPLWIN32_HPP
#define TTSFML_JOYSTICKIMPLWIN32_HPP

#ifdef _WIN32_WINDOWS
    #undef _WIN32_WINDOWS
#endif
#ifdef _WIN32_WINNT
    #undef _WIN32_WINNT
#endif
#define _WIN32_WINDOWS      0x0501
#define _WIN32_WINNT        0x0501
#define DIRECTINPUT_VERSION 0x0800
#include <Window/Joystick.hpp>
#include <Window/JoystickImpl.hpp>
#include <System/String.hpp>
#include <windows.h>
#include <mmsystem.h>
#include <dinput.h>


namespace ttsf
{
namespace priv
{

class JoystickImpl
{
public:

    static void initialize();

    static void cleanup();

    static bool isConnected(unsigned int index);

    static void setLazyUpdates(bool status);

    static void updateConnections();

    bool open(unsigned int index);

    void close();

    JoystickCaps getCapabilities() const;

    Joystick::Identification getIdentification() const;

    JoystickState update();

    static void initializeDInput();

    static void cleanupDInput();

    static bool isConnectedDInput(unsigned int index);

    static void updateConnectionsDInput();

    bool openDInput(unsigned int index);

    void closeDInput();

    JoystickCaps getCapabilitiesDInput() const;

    JoystickState updateDInput();

private:

    static BOOL CALLBACK deviceEnumerationCallback(const DIDEVICEINSTANCE* deviceInstance, void* userData);

    static BOOL CALLBACK deviceObjectEnumerationCallback(const DIDEVICEOBJECTINSTANCE* deviceObjectInstance, void* userData);

    unsigned int             m_index;                          ///< Index of the joystick
    JOYCAPS                  m_caps;                           ///< Joystick capabilities
    IDirectInputDevice8W*    m_device;                         ///< DirectInput 8.x device
    DIDEVCAPS                m_deviceCaps;                     ///< DirectInput device capabilities
    int                      m_axes[Joystick::AxisCount];      ///< Offsets to the bytes containing the axes states, -1 if not available
    int                      m_buttons[Joystick::ButtonCount]; ///< Offsets to the bytes containing the button states, -1 if not available
    Joystick::Identification m_identification;                 ///< Joystick identification
};

} // namespace priv

} // namespace sf


#endif // SFML_JOYSTICKIMPLWIN32_HPP
