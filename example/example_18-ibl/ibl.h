
#ifndef IBL_H_426AA2232FB4B477BD71333A51418F16
#define IBL_H_426AA2232FB4B477BD71333A51418F16


#include <stdint.h>  // int32_t

#include <bgfx/bgfx.h>
#include <bgfx/bgfx_utils.h>

#include <bx/timer.h>
#include <bx/math.h>

#include <tinystl/allocator.h>
#include <tinystl/vector.h>
#include <tinystl/string.h>
namespace stl = tinystl;

#include <bgfx/bgfx.h>
#include <bx/commandline.h>
#include <bx/endian.h>
#include <bx/math.h>
#include <bx/readerwriter.h>
#include <bx/bxstring.h>
#include <ib-compress/indexbufferdecompression.h>

#include <bimg/decode.h>

#include <string>

#include <bx/macros.h>
#include <bx/uint32_t.h>

#include <bimg/decode.h>

#include <bx/allocator.h>
#include <bx/readerwriter.h>
#include <bx/file.h>

#include <bimg/bimg.h>

#include <sxbCommon/defines.h>
#include <sxbCommon/Mesh.h>
#include <sxbCommon/utils.h>

#pragma mark -

static float s_texelHalf = 0.0f;

struct Uniforms
{
    enum { NumVec4 = 12 };
    
    void init()
    {
        u_params = bgfx::createUniform("u_params", bgfx::UniformType::Vec4, NumVec4);
    }
    
    void submit()
    {
        bgfx::setUniform(u_params, m_params, NumVec4);
    }
    
    void destroy()
    {
        bgfx::destroy(u_params);
    }
    
    union
    {
        struct
        {
            union
            {
                float m_mtx[16];
                /* 0*/ struct { float m_mtx0[4]; };
                /* 1*/ struct { float m_mtx1[4]; };
                /* 2*/ struct { float m_mtx2[4]; };
                /* 3*/ struct { float m_mtx3[4]; };
            };
            /* 4*/ struct { float m_glossiness, m_reflectivity, m_exposure, m_bgType; };
            /* 5*/ struct { float m_metalOrSpec, m_unused5[3]; };
            /* 6*/ struct { float m_doDiffuse, m_doSpecular, m_doDiffuseIbl, m_doSpecularIbl; };
            /* 7*/ struct { float m_cameraPos[3], m_unused7[1]; };
            /* 8*/ struct { float m_rgbDiff[4]; };
            /* 9*/ struct { float m_rgbSpec[4]; };
            /*10*/ struct { float m_lightDir[3], m_unused10[1]; };
            /*11*/ struct { float m_lightCol[3], m_unused11[1]; };
        };
        
        float m_params[NumVec4*4];
    };
    
    bgfx::UniformHandle u_params;
};

struct LightProbe
{
    enum Enum
    {
        Bolonga,
        Kyoto,
        
        Count
    };
    
    void load(const char* _name)
    {
        char filePath[512];
        
        bx::snprintf(filePath, BX_COUNTOF(filePath), "textures/%s_lod.dds", _name);
        // todo(gzy)
        m_tex = sxb::Utils::loadTexture(filePath, BGFX_SAMPLER_U_CLAMP|BGFX_SAMPLER_V_CLAMP|BGFX_SAMPLER_W_CLAMP);
        
        bx::snprintf(filePath, BX_COUNTOF(filePath), "textures/%s_irr.dds", _name);
        m_texIrr = sxb::Utils::loadTexture(filePath, BGFX_SAMPLER_U_CLAMP|BGFX_SAMPLER_V_CLAMP|BGFX_SAMPLER_W_CLAMP);
    }
    
    void destroy()
    {
        bgfx::destroy(m_tex);
        bgfx::destroy(m_texIrr);
    }
    
    bgfx::TextureHandle m_tex;
    bgfx::TextureHandle m_texIrr;
};

struct Camera
{
    Camera()
    {
        reset();
    }
    
    void reset()
    {
        m_target.curr = { 0.0f, 0.0f, 0.0f };
        m_target.dest = { 0.0f, 0.0f, 0.0f };
        
        m_pos.curr = { 0.0f, 0.0f, -3.0f };
        m_pos.dest = { 0.0f, 0.0f, -3.0f };
        
        m_orbit[0] = 0.0f;
        m_orbit[1] = 0.0f;
    }
    
    void mtxLookAt(float* _outViewMtx)
    {
        bx::mtxLookAt(_outViewMtx, m_pos.curr, m_target.curr);
    }
    
    void orbit(float _dx, float _dy)
    {
        m_orbit[0] += _dx;
        m_orbit[1] += _dy;
    }
    
    void dolly(float _dz)
    {
        const float cnear = 1.0f;
        const float cfar  = 100.0f;
        
        const bx::Vec3 toTarget     = bx::sub(m_target.dest, m_pos.dest);
        const float toTargetLen     = bx::length(toTarget);
        const float invToTargetLen  = 1.0f / (toTargetLen + bx::kFloatMin);
        const bx::Vec3 toTargetNorm = bx::mul(toTarget, invToTargetLen);
        
        float delta  = toTargetLen * _dz;
        float newLen = toTargetLen + delta;
        if ( (cnear  < newLen || _dz < 0.0f)
            &&   (newLen < cfar   || _dz > 0.0f) )
        {
            m_pos.dest = bx::mad(toTargetNorm, delta, m_pos.dest);
        }
    }
    
    void consumeOrbit(float _amount)
    {
        float consume[2];
        consume[0] = m_orbit[0] * _amount;
        consume[1] = m_orbit[1] * _amount;
        m_orbit[0] -= consume[0];
        m_orbit[1] -= consume[1];
        
        const bx::Vec3 toPos     = bx::sub(m_pos.curr, m_target.curr);
        const float toPosLen     = bx::length(toPos);
        const float invToPosLen  = 1.0f / (toPosLen + bx::kFloatMin);
        const bx::Vec3 toPosNorm = bx::mul(toPos, invToPosLen);
        
        float ll[2];
        bx::toLatLong(&ll[0], &ll[1], toPosNorm);
        ll[0] += consume[0];
        ll[1] -= consume[1];
        ll[1]  = bx::clamp(ll[1], 0.02f, 0.98f);
        
        const bx::Vec3 tmp  = bx::fromLatLong(ll[0], ll[1]);
        const bx::Vec3 diff = bx::mul(bx::sub(tmp, toPosNorm), toPosLen);
        
        m_pos.curr = bx::add(m_pos.curr, diff);
        m_pos.dest = bx::add(m_pos.dest, diff);
    }
    
    void update(float _dt)
    {
        const float amount = bx::min(_dt / 0.12f, 1.0f);
        
        consumeOrbit(amount);
        
        m_target.curr = bx::lerp(m_target.curr, m_target.dest, amount);
        m_pos.curr    = bx::lerp(m_pos.curr,    m_pos.dest,    amount);
    }
    
    void envViewMtx(float* _mtx)
    {
        const bx::Vec3 toTarget     = bx::sub(m_target.curr, m_pos.curr);
        const float toTargetLen     = bx::length(toTarget);
        const float invToTargetLen  = 1.0f / (toTargetLen + bx::kFloatMin);
        const bx::Vec3 toTargetNorm = bx::mul(toTarget, invToTargetLen);
        
        const bx::Vec3 right = bx::normalize(bx::cross({ 0.0f, 1.0f, 0.0f }, toTargetNorm) );
        const bx::Vec3 up    = bx::normalize(bx::cross(toTargetNorm, right) );
        
        _mtx[ 0] = right.x;
        _mtx[ 1] = right.y;
        _mtx[ 2] = right.z;
        _mtx[ 3] = 0.0f;
        _mtx[ 4] = up.x;
        _mtx[ 5] = up.y;
        _mtx[ 6] = up.z;
        _mtx[ 7] = 0.0f;
        _mtx[ 8] = toTargetNorm.x;
        _mtx[ 9] = toTargetNorm.y;
        _mtx[10] = toTargetNorm.z;
        _mtx[11] = 0.0f;
        _mtx[12] = 0.0f;
        _mtx[13] = 0.0f;
        _mtx[14] = 0.0f;
        _mtx[15] = 1.0f;
    }
    
    struct Interp3f
    {
        bx::Vec3 curr;
        bx::Vec3 dest;
    };
    
    Interp3f m_target;
    Interp3f m_pos;
    float m_orbit[2];
};

struct Mouse
{
    Mouse()
    : m_dx(0.0f)
    , m_dy(0.0f)
    , m_prevMx(0.0f)
    , m_prevMy(0.0f)
    , m_scroll(0)
    , m_scrollPrev(0)
    {
    }
    
    void update(float _mx, float _my, int32_t _mz, uint32_t _width, uint32_t _height)
    {
        const float widthf  = float(int32_t(_width));
        const float heightf = float(int32_t(_height));
        
        // Delta movement.
        m_dx = float(_mx - m_prevMx)/widthf;
        m_dy = float(_my - m_prevMy)/heightf;
        
        m_prevMx = _mx;
        m_prevMy = _my;
        
        // Scroll.
        m_scroll = _mz - m_scrollPrev;
        m_scrollPrev = _mz;
    }
    
    float m_dx; // Screen space.
    float m_dy;
    float m_prevMx;
    float m_prevMy;
    int32_t m_scroll;
    int32_t m_scrollPrev;
};

struct Settings
{
    Settings()
    {
        m_envRotCurr = 0.0f;
        m_envRotDest = 0.0f;
        m_lightDir[0] = -0.8f;
        m_lightDir[1] = 0.2f;
        m_lightDir[2] = -0.5f;
        m_lightCol[0] = 1.0f;
        m_lightCol[1] = 1.0f;
        m_lightCol[2] = 1.0f;
        m_glossiness = 0.7f;
        m_exposure = 0.0f;
        m_bgType = 3.0f;
        m_radianceSlider = 2.0f;
        m_reflectivity = 0.85f;
        m_rgbDiff[0] = 1.0f;
        m_rgbDiff[1] = 1.0f;
        m_rgbDiff[2] = 1.0f;
        m_rgbSpec[0] = 1.0f;
        m_rgbSpec[1] = 1.0f;
        m_rgbSpec[2] = 1.0f;
        m_lod = 0.0f;
        m_doDiffuse = false;
        m_doSpecular = false;
        m_doDiffuseIbl = true;
        m_doSpecularIbl = true;
        m_showLightColorWheel = true;
        m_showDiffColorWheel = true;
        m_showSpecColorWheel = true;
        m_metalOrSpec = 0;
        m_meshSelection = 0;
    }
    
    float m_envRotCurr;
    float m_envRotDest;
    float m_lightDir[3];
    float m_lightCol[3];
    float m_glossiness;
    float m_exposure;
    float m_radianceSlider;
    float m_bgType;
    float m_reflectivity;
    float m_rgbDiff[3];
    float m_rgbSpec[3];
    float m_lod;
    bool  m_doDiffuse;
    bool  m_doSpecular;
    bool  m_doDiffuseIbl;
    bool  m_doSpecularIbl;
    bool  m_showLightColorWheel;
    bool  m_showDiffColorWheel;
    bool  m_showSpecColorWheel;
    int32_t m_metalOrSpec;
    int32_t m_meshSelection;
};

#pragma mark -

class ibl
{
public:
	ibl()
    : m_ready(false)
    {}
    
	~ibl()
	{
		bgfx::shutdown();
	}

public:
	bool init(void* nwh_);

	void update(const uint64_t & frame_ = 0);
    
    void touchBegin(const int &x_, const int &y_)
    {
        m_touch_x = x_;
        m_touch_y = y_;
    }
    
    void touchMove(const int &x_, const int &y_)
    {
        m_delta_x = x_ - m_touch_x;
        m_delta_y = y_ - m_touch_y;
        m_touch_x = x_;
        m_touch_y = y_;
    }
    
    void touchEnd(const int &x_, const int &y_)
    {
        m_delta_x = 0;
        m_delta_y = 0;
    }
    
private:
	bool m_ready;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
    
    int     m_touch_x {0};
    int     m_touch_y {0};
    
    int     m_delta_x {0};
    int     m_delta_y {0};

    Uniforms m_uniforms;
    
    LightProbe m_lightProbes[LightProbe::Count];
    LightProbe::Enum m_currentLightProbe;
    
    bgfx::UniformHandle u_mtx;
    bgfx::UniformHandle u_params;
    bgfx::UniformHandle u_flags;
    bgfx::UniformHandle u_camPos;
    bgfx::UniformHandle s_texCube;
    bgfx::UniformHandle s_texCubeIrr;
    
    bgfx::ProgramHandle m_programMesh;
    bgfx::ProgramHandle m_programSky;
    
    sxb::Mesh           m_meshBunny;
    sxb::Mesh           m_meshOrb;
    Camera              m_camera;
    Mouse               m_mouse;
    
    Settings m_settings;
};


#endif // IBL_H_426AA2232FB4B477BD71333A51418F16
