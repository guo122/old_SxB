
#ifndef TTSFML_MUTEX_HPP
#define TTSFML_MUTEX_HPP

#include <System/Export.hpp>
#include <System/NonCopyable.hpp>

namespace ttsf
{
namespace priv
{
    class MutexImpl;
}

class TTSFML_SYSTEM_API Mutex : NonCopyable
{
public:

    Mutex();

    ~Mutex();

    void lock();

    void unlock();

private:

    priv::MutexImpl* m_mutexImpl; ///< OS-specific implementation
};

} // namespace sf


#endif // SFML_MUTEX_HPP

