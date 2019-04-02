
#ifndef TTSFML_SENSORIMPLWIN32_HPP
#define TTSFML_SENSORIMPLWIN32_HPP


namespace ttsf
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

} // namespace sf


#endif // SFML_SENSORIMPLWIN32_HPP
