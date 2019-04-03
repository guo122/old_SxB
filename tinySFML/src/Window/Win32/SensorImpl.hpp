
#ifndef TTSFML_SENSORIMPLWIN32_HPP
#define TTSFML_SENSORIMPLWIN32_HPP


namespace tinySFML
{
namespace priv
{

class SensorImpl
{
public:

    static void initialize();

    static void cleanup();

    static bool isAvailable(Sensor::Type sensor);

    bool open(Sensor::Type sensor);

    void close();

    Vector3f update();

    void setEnabled(bool enabled);
};

} // namespace priv

} // namespace tinySFML


#endif // SFML_SENSORIMPLWIN32_HPP
