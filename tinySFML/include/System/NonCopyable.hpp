
#ifndef TTSFML_NONCOPYABLE_HPP
#define TTSFML_NONCOPYABLE_HPP

#include <System/Export.hpp>

namespace ttsf
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

} // namespace ttsf


#endif // TTSFML_NONCOPYABLE_HPP
