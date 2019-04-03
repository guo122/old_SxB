
#ifndef TTSFML_LOCK_HPP
#define TTSFML_LOCK_HPP

#include <System/Export.hpp>
#include <System/NonCopyable.hpp>

namespace tinySFML
{
class Mutex;

class TTSFML_SYSTEM_API Lock : NonCopyable
{
public:

    explicit Lock(Mutex& mutex);

    ~Lock();

private:

    Mutex& m_mutex; ///< Mutex to lock / unlock
};

} // namespace sf


#endif // SFML_LOCK_HPP

