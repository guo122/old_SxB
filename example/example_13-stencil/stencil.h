
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
	stencil()
    : m_ready(false)
    , m_cursorX(0)
    , m_cursorY(0)
    , m_deltaX(0)
    , m_deltaY(0)
    {}
    
	~stencil()
	{
		bgfx::shutdown();
	}

public:
	bool init(void* nwh_);

	void update(const uint64_t & frame_ = 0);
    
    void setCursor(const int &x_, const int &y_)
    {
        m_deltaX += x_ - m_cursorX;
        m_deltaY += y_ - m_cursorY;
        m_cursorX = x_, m_cursorY = y_;
    }

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
    float m_lightRgbInnerR[MAX_NUM_LIGHTS][4];
    
//    Scene m_scene;
    int32_t m_numLights;
    float   m_reflectionValue;
    bool    m_updateLights;
    bool    m_updateScene;
    
    int     m_cursorX;
    int     m_cursorY;
    
    int     m_deltaX;
    int     m_deltaY;
    
    sxb::Uniforms m_uniforms;
//    ClearValues m_clearValues;
};

#endif // STENCIL_H_B874E9B544F90998EF3FC1D95074912E
