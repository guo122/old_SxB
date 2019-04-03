
#ifndef TTSFML_TIME_HPP
#define TTSFML_TIME_HPP

#include <System/Export.hpp>

namespace tinySFML
{

class TTSFML_SYSTEM_API Time
{
public:

    Time();

    float asSeconds() const;

    Int32 asMilliseconds() const;

    Int64 asMicroseconds() const;

    static const Time Zero; ///< Predefined "zero" time value

private:

    friend TTSFML_SYSTEM_API Time seconds(float);
    friend TTSFML_SYSTEM_API Time milliseconds(Int32);
    friend TTSFML_SYSTEM_API Time microseconds(Int64);

    explicit Time(Int64 microseconds);

private:

    Int64 m_microseconds; ///< Time value stored as microseconds
};

TTSFML_SYSTEM_API Time seconds(float amount);

TTSFML_SYSTEM_API Time milliseconds(Int32 amount);

TTSFML_SYSTEM_API Time microseconds(Int64 amount);

TTSFML_SYSTEM_API bool operator ==(Time left, Time right);

TTSFML_SYSTEM_API bool operator !=(Time left, Time right);

TTSFML_SYSTEM_API bool operator <(Time left, Time right);

TTSFML_SYSTEM_API bool operator >(Time left, Time right);

TTSFML_SYSTEM_API bool operator <=(Time left, Time right);

TTSFML_SYSTEM_API bool operator >=(Time left, Time right);

TTSFML_SYSTEM_API Time operator -(Time right);

TTSFML_SYSTEM_API Time operator +(Time left, Time right);

TTSFML_SYSTEM_API Time& operator +=(Time& left, Time right);

TTSFML_SYSTEM_API Time operator -(Time left, Time right);

TTSFML_SYSTEM_API Time& operator -=(Time& left, Time right);

TTSFML_SYSTEM_API Time operator *(Time left, float right);

TTSFML_SYSTEM_API Time operator *(Time left, Int64 right);

TTSFML_SYSTEM_API Time operator *(float left, Time right);

TTSFML_SYSTEM_API Time operator *(Int64 left, Time right);

TTSFML_SYSTEM_API Time& operator *=(Time& left, float right);

TTSFML_SYSTEM_API Time& operator *=(Time& left, Int64 right);

TTSFML_SYSTEM_API Time operator /(Time left, float right);

TTSFML_SYSTEM_API Time operator /(Time left, Int64 right);

TTSFML_SYSTEM_API Time& operator /=(Time& left, float right);

TTSFML_SYSTEM_API Time& operator /=(Time& left, Int64 right);

TTSFML_SYSTEM_API float operator /(Time left, Time right);

TTSFML_SYSTEM_API Time operator %(Time left, Time right);

TTSFML_SYSTEM_API Time& operator %=(Time& left, Time right);

} // namespace sf

#endif // SFML_TIME_HPP
