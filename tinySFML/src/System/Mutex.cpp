
#include <System/Mutex.hpp>

#if defined(SFML_SYSTEM_WINDOWS)
    #include <System/Win32/MutexImpl.hpp>
#else
    #include <Unix/MutexImpl.hpp>
#endif

namespace ttsf
{
////////////////////////////////////////////////////////////
Mutex::Mutex()
{
    m_mutexImpl = new priv::MutexImpl;
}


////////////////////////////////////////////////////////////
Mutex::~Mutex()
{
    delete m_mutexImpl;
}


////////////////////////////////////////////////////////////
void Mutex::lock()
{
    m_mutexImpl->lock();
}


////////////////////////////////////////////////////////////
void Mutex::unlock()
{
    m_mutexImpl->unlock();
}

} // namespace sf
