
#include <System/Sleep.hpp>

#if defined(SFML_SYSTEM_WINDOWS)
    #include <System/Win32/SleepImpl.hpp>
#else
    #include <System/Unix/SleepImpl.hpp>
#endif


namespace tinySFML
{
////////////////////////////////////////////////////////////
void sleep(Time duration)
{
    if (duration >= Time::Zero)
        priv::sleepImpl(duration);
}

} // namespace sf
