
#ifndef TTSFML_SENSORMANAGER_HPP
#define TTSFML_SENSORMANAGER_HPP

#include <Window/Sensor.hpp>
#include <Window/SensorImpl.hpp>
#include <System/NonCopyable.hpp>


namespace ttsf
{
namespace priv
{

class SensorManager : NonCopyable
{
public:

    static SensorManager& getInstance();

    bool isAvailable(Sensor::Type sensor);

    void setEnabled(Sensor::Type sensor, bool enabled);

    bool isEnabled(Sensor::Type sensor) const;

    Vector3f getValue(Sensor::Type sensor) const;

    void update();

private:

    SensorManager();

    ~SensorManager();

    struct Item
    {
        bool available;    ///< Is the sensor available on this device?
        bool enabled;      ///< Current enable state of the sensor
        SensorImpl sensor; ///< Sensor implementation
        Vector3f value;    ///< The current sensor value
    };

    Item m_sensors[Sensor::Count]; ///< Sensors information and state
};

} // namespace priv

} // namespace sf


#endif // SFML_SENSORMANAGER_HPP
