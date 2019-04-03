
#ifndef TTSFML_CLOCK_HPP
#define TTSFML_CLOCK_HPP

#include <System/Export.hpp>
#include <System/Time.hpp>

namespace tinySFML
{

class TTSFML_SYSTEM_API Clock
{
public:

    Clock();

    Time getElapsedTime() const;

    Time restart();

private:

    Time m_startTime; ///< Time of last reset, in microseconds
};

} // namespace sf

#endif // SFML_CLOCK_HPP

