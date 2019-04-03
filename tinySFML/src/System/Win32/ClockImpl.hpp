
#ifndef TTSFML_CLOCKIMPLWIN32_HPP
#define TTSFML_CLOCKIMPLWIN32_HPP

#include <Config.hpp>
#include <System/Time.hpp>

namespace tinySFML
{
namespace priv
{

class ClockImpl
{
public:

    static Time getCurrentTime();
};

} // namespace priv

} // namespace sf


#endif // SFML_CLOCKIMPLWIN32_HPP
