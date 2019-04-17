
#ifndef STENCIL_H_B874E9B544F90998EF3FC1D95074912E
#define STENCIL_H_B874E9B544F90998EF3FC1D95074912E


#include <stdint.h>  // int32_t

#include <bgfx/bgfx.h>
#include <bgfx/bgfx_utils.h>

#include <sxbCommon/defines.h>
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

    sxb::Mesh m_bunnyMesh;
    sxb::Mesh m_columnMesh;
    sxb::Mesh m_cubeMesh;
    sxb::Mesh m_hplaneMesh;
    sxb::Mesh m_vplaneMesh;

    bgfx::ProgramHandle m_programTextureLighting;
    bgfx::ProgramHandle m_programColorLighting;
    bgfx::ProgramHandle m_programColorTexture;
    bgfx::ProgramHandle m_programColorBlack;
    bgfx::ProgramHandle m_programTexture;
    
    bgfx::TextureHandle m_figureTex;
    bgfx::TextureHandle m_flareTex;
    bgfx::TextureHandle m_fieldstoneTex;
    
    double m_residentMem;
    double m_virtualMem;
    
    bgfx::UniformHandle m_texColor;
//    ClearValues m_clearValues;
};

#endif // STENCIL_H_B874E9B544F90998EF3FC1D95074912E
