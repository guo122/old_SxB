
#ifndef COC_H_7B4975ED05CC0EE7517EAAC13D1DC8A8
#define COC_H_7B4975ED05CC0EE7517EAAC13D1DC8A8

#include <stdint.h>  // int32_t

#include <bgfx/bgfx.h>
#include <bgfx/bgfx_utils.h>

#include <sxbCommon/defines.h>
#include <sxbCommon/Mesh.h>

struct v2
{
    v2():key(false),x(0),y(0){}
    
    void clear(){key = false, x = 0, y = 0;}
    bool key;
    int x;
    int y;
};

class Coc
{
public:
	Coc()
    : m_ready(false)
    , m_sceneTime(0.0)
    , m_mountainD(0.0)
    {};
	~Coc() {}

public:
	bool init(void* nwh_);

	void update(const uint64_t & frame_ = 0);
    
    void touchBegin(const int &x_, const int &y_) {m_touch.x = x_, m_touch.y = y_;}
    
    void touchMove(const int &x_, const int &y_)
    {
        m_delta.x += x_ - m_touch.x;
        m_delta.y += y_ - m_touch.y;
        m_touch.x = x_, m_touch.y = y_;
    }
    
    void touchEnd() {m_delta.clear();}

private:
	bool m_ready;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

    sxb::Mesh m_bunnyMesh;
    sxb::Mesh m_mountainMesh;
    sxb::Mesh m_roadMesh;

	bgfx::ProgramHandle m_program;
    
	bgfx::UniformHandle s_texColor;
	bgfx::UniformHandle s_texStipple;
	bgfx::UniformHandle u_stipple;

	bgfx::TextureHandle m_textureStipple;
	bgfx::TextureHandle m_textureLeafs;
	bgfx::TextureHandle m_textureBark;
    double m_sceneTime;
    double m_mountainD;
    
    double m_residentMem;
    double m_virtualMem;
    
    v2  m_touch;
    v2  m_delta;
    
    v2  m_pos;
};

#endif // COC_H_7B4975ED05CC0EE7517EAAC13D1DC8A8
