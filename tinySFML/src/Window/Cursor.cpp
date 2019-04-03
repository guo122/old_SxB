
#include <Window/Cursor.hpp>
#include <Window/CursorImpl.hpp>

namespace tinySFML
{

////////////////////////////////////////////////////////////
Cursor::Cursor() :
m_impl(new priv::CursorImpl())
{
    // That's it
}


////////////////////////////////////////////////////////////
Cursor::~Cursor()
{
    delete m_impl;
}


////////////////////////////////////////////////////////////
bool Cursor::loadFromPixels(const Uint8* pixels, Vector2u size, Vector2u hotspot)
{
    if ((pixels == 0) || (size.x == 0) || (size.y == 0))
        return false;
    else
        return m_impl->loadFromPixels(pixels, size, hotspot);
}


////////////////////////////////////////////////////////////
bool Cursor::loadFromSystem(Type type)
{
    return m_impl->loadFromSystem(type);
}


////////////////////////////////////////////////////////////
const priv::CursorImpl& Cursor::getImpl() const
{
    return *m_impl;
}

} // namespace tinySFML

