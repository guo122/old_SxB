
#ifndef TTSFML_MUTEXIMPL_HPP
#define TTSFML_MUTEXIMPL_HPP

#include <System/NonCopyable.hpp>
#include <windows.h>

namespace tinySFML
{
namespace priv
{

class MutexImpl : NonCopyable
{
public:

    MutexImpl();

    ~MutexImpl();

    void lock();

    void unlock();

private:

    CRITICAL_SECTION m_mutex; ///< Win32 handle of the mutex
};

} // namespace priv

} // namespace sf


#endif // SFML_MUTEXIMPL_HPP
