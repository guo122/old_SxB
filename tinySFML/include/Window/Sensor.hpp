
#ifndef TTSFML_SENSOR_HPP
#define TTSFML_SENSOR_HPP

#include <Window/Export.hpp>
#include <System/Vector3.hpp>
#include <System/Time.hpp>


namespace ttsf
{

class TTSFML_WINDOW_API Sensor
{
public:

    enum Type
    {
        Accelerometer,    ///< Measures the raw acceleration (m/s^2)
        Gyroscope,        ///< Measures the raw rotation rates (degrees/s)
        Magnetometer,     ///< Measures the ambient magnetic field (micro-teslas)
        Gravity,          ///< Measures the direction and intensity of gravity, independent of device acceleration (m/s^2)
        UserAcceleration, ///< Measures the direction and intensity of device acceleration, independent of the gravity (m/s^2)
        Orientation,      ///< Measures the absolute 3D orientation (degrees)

        Count             ///< Keep last -- the total number of sensor types
    };

    static bool isAvailable(Type sensor);

    static void setEnabled(Type sensor, bool enabled);

    static Vector3f getValue(Type sensor);
};

} // namespace sf


#endif // SFML_SENSOR_HPP
