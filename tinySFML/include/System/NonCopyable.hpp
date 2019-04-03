
#ifndef TTSFML_NONCOPYABLE_HPP
#define TTSFML_NONCOPYABLE_HPP

#include <System/Export.hpp>

namespace tinySFML
{

class TTSFML_SYSTEM_API NonCopyable
{
protected:

    NonCopyable() {}
    ~NonCopyable() {}

private:

    NonCopyable(const NonCopyable&);

    NonCopyable& operator =(const NonCopyable&);
};

} // namespace tinySFML


#endif // TTSFML_NONCOPYABLE_HPP
