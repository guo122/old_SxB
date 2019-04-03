
#include <System/Win32/ClockImpl.hpp>
#include <System/Mutex.hpp>
#include <System/Lock.hpp>
#include <windows.h>

namespace
{
    LARGE_INTEGER getFrequency()
    {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        return frequency;
    }

    bool isWindowsXpOrOlder()
    {
        // Windows XP was the last 5.x version of Windows
        return static_cast<DWORD>(LOBYTE(LOWORD(GetVersion()))) < 6;
    }
}

namespace tinySFML
{
namespace priv
{
////////////////////////////////////////////////////////////
Time ClockImpl::getCurrentTime()
{
    // Get the frequency of the performance counter
    // (it is constant across the program lifetime)
    static LARGE_INTEGER frequency = getFrequency();

    // Detect if we are on Windows XP or older
    static bool oldWindows = isWindowsXpOrOlder();

    LARGE_INTEGER time;

    if (oldWindows)
    {
        static tinySFML::Mutex oldWindowsMutex;

        // Acquire a lock (CRITICAL_SECTION) to prevent travelling back in time
        Lock lock(oldWindowsMutex);

        // Get the current time
        QueryPerformanceCounter(&time);
    }
    else
    {
        // Get the current time
        QueryPerformanceCounter(&time);
    }

    // Return the current time as microseconds
    return tinySFML::microseconds(1000000 * time.QuadPart / frequency.QuadPart);
}

} // namespace priv

} // namespace sf
