
#ifndef TTSFML_VIDEOMODE_HPP
#define TTSFML_VIDEOMODE_HPP

#include <Window/Export.hpp>
#include <vector>

namespace tinySFML
{

class TTSFML_WINDOW_API VideoMode
{
public:

    VideoMode();

    VideoMode(unsigned int modeWidth, unsigned int modeHeight, unsigned int modeBitsPerPixel = 32);

    static VideoMode getDesktopMode();

    static const std::vector<VideoMode>& getFullscreenModes();

    bool isValid() const;

    unsigned int width;        ///< Video mode width, in pixels
    unsigned int height;       ///< Video mode height, in pixels
    unsigned int bitsPerPixel; ///< Video mode pixel depth, in bits per pixels
};

TTSFML_WINDOW_API bool operator ==(const VideoMode& left, const VideoMode& right);

TTSFML_WINDOW_API bool operator !=(const VideoMode& left, const VideoMode& right);

TTSFML_WINDOW_API bool operator <(const VideoMode& left, const VideoMode& right);

TTSFML_WINDOW_API bool operator >(const VideoMode& left, const VideoMode& right);

TTSFML_WINDOW_API bool operator <=(const VideoMode& left, const VideoMode& right);

TTSFML_WINDOW_API bool operator >=(const VideoMode& left, const VideoMode& right);

} // namespace tinySFML


#endif // SFML_VIDEOMODE_HPP