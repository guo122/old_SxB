
#include <System/Clock.hpp>

#if defined(SFML_SYSTEM_WINDOWS)
	#include <System/Win32/ClockImpl.hpp>
#else
    #include <System/Unix/ClockImpl.hpp>
#endif

namespace ttsf
{
////////////////////////////////////////////////////////////
Clock::Clock() :
m_startTime(priv::ClockImpl::getCurrentTime())
{
}


////////////////////////////////////////////////////////////
Time Clock::getElapsedTime() const
{
    return priv::ClockImpl::getCurrentTime() - m_startTime;
}


////////////////////////////////////////////////////////////
Time Clock::restart()
{
    Time now = priv::ClockImpl::getCurrentTime();
    Time elapsed = now - m_startTime;
    m_startTime = now;

    return elapsed;
}

} // namespace sf
