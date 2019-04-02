
#include <System/Lock.hpp>
#include <System/Mutex.hpp>

namespace ttsf
{
////////////////////////////////////////////////////////////
Lock::Lock(Mutex& mutex) :
m_mutex(mutex)
{
    m_mutex.lock();
}


////////////////////////////////////////////////////////////
Lock::~Lock()
{
    m_mutex.unlock();
}

} // namespace sf
