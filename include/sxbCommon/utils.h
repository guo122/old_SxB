
#ifndef UTILS_H_D7F61747FB3C5E68C6A972C2521B0AC2
#define UTILS_H_D7F61747FB3C5E68C6A972C2521B0AC2

#include "sxbTop/defines.h"

namespace bgfx
{
	class ShaderHandle;
}

SXB_NAMESPACE_BEGIN

class Utils
{
public:
	static bool loadShader(const char *FILENAME, bgfx::ShaderHandle & sh_);

private:
	Utils() {};
	~Utils() {};
};

SXB_NAMESPACE_END

#endif // UTILS_H_D7F61747FB3C5E68C6A972C2521B0AC2