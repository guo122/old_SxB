
#ifndef TTSFML_VIDEOMODEIMPL_HPP
#define TTSFML_VIDEOMODEIMPL_HPP

#include <Window/VideoMode.hpp>

namespace tinySFML
{
namespace priv
{

class VideoModeImpl
{
public:

    static std::vector<VideoMode> getFullscreenModes();

    static VideoMode getDesktopMode();
};

} // namespace priv

} // namespace tinySFML


#endif // SFML_VIDEOMODEIMPL_HPP
