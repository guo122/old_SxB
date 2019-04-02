
#include <Window/Sensor.hpp>
#include <Window/SensorManager.hpp>

namespace ttsf
{

////////////////////////////////////////////////////////////
bool Sensor::isAvailable(Type sensor)
{
    return priv::SensorManager::getInstance().isAvailable(sensor);
}

////////////////////////////////////////////////////////////
void Sensor::setEnabled(Type sensor, bool enabled)
{
    return priv::SensorManager::getInstance().setEnabled(sensor, enabled);
}

////////////////////////////////////////////////////////////
Vector3f Sensor::getValue(Type sensor)
{
    return priv::SensorManager::getInstance().getValue(sensor);
}

} // namespace sf
