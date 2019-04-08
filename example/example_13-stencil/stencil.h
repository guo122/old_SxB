
#ifndef STENCIL_H_B874E9B544F90998EF3FC1D95074912E
#define STENCIL_H_B874E9B544F90998EF3FC1D95074912E


#include <stdint.h>  // int32_t

#include <bgfx/bgfx.h>
#include <bgfx/bgfx_utils.h>

#include <sxbTop/defines.h>
#include <sxbCommon/Mesh.h>

class stencil
{
public:
	stencil(): m_ready(false) {}
	~stencil()
	{
		bgfx::shutdown();
	}

public:
	bool init(void* nwh_);

	void update(const uint64_t & frame_ = 0);

private:
	bool m_ready;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	sxb::Mesh* m_bunnyMesh;

	bgfx::ProgramHandle m_program;
};

#endif // STENCIL_H_B874E9B544F90998EF3FC1D95074912E