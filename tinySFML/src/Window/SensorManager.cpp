
#include <Window/SensorManager.hpp>
#include <System/Err.hpp>


namespace tinySFML
{
namespace priv
{
////////////////////////////////////////////////////////////
SensorManager& SensorManager::getInstance()
{
    static SensorManager instance;
    return instance;
}


////////////////////////////////////////////////////////////
bool SensorManager::isAvailable(Sensor::Type sensor)
{
    return m_sensors[sensor].available;
}


////////////////////////////////////////////////////////////
void SensorManager::setEnabled(Sensor::Type sensor, bool enabled)
{
    if (m_sensors[sensor].available)
    {
        m_sensors[sensor].enabled = enabled;
        m_sensors[sensor].sensor.setEnabled(enabled);
    }
    else
    {
        err() << "Warning: trying to enable a sensor that is not available (call Sensor::isAvailable to check it)" << std::endl;
    }
}


////////////////////////////////////////////////////////////
bool SensorManager::isEnabled(Sensor::Type sensor) const
{
    return m_sensors[sensor].enabled;
}


////////////////////////////////////////////////////////////
Vector3f SensorManager::getValue(Sensor::Type sensor) const
{
    return m_sensors[sensor].value;
}


////////////////////////////////////////////////////////////
void SensorManager::update()
{
    for (int i = 0; i < Sensor::Count; ++i)
    {
        // Only process available sensors
        if (m_sensors[i].available)
            m_sensors[i].value = m_sensors[i].sensor.update();
    }
}


////////////////////////////////////////////////////////////
SensorManager::SensorManager()
{
    // Global sensor initialization
    SensorImpl::initialize();

    // Per sensor initialization
    for (int i = 0; i < Sensor::Count; ++i)
    {
        // Check which sensors are available
        m_sensors[i].available = SensorImpl::isAvailable(static_cast<Sensor::Type>(i));

        // Open the available sensors
        if (m_sensors[i].available)
        {
            m_sensors[i].sensor.open(static_cast<Sensor::Type>(i));
            m_sensors[i].sensor.setEnabled(false);
        }
    }
}

////////////////////////////////////////////////////////////
SensorManager::~SensorManager()
{
    // Per sensor cleanup
    for (int i = 0; i < Sensor::Count; ++i)
    {
        if (m_sensors[i].available)
            m_sensors[i].sensor.close();
    }

    // Global sensor cleanup
    SensorImpl::cleanup();
}

} // namespace priv

} // namespace tinySFML
