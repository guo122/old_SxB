
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/math.h>
#include <bx/readerwriter.h>
#include <sxbCommon/utils.h>
#include "stencil.h"



#define RENDER_VIEWID_RANGE1_PASS_0  1
#define RENDER_VIEWID_RANGE1_PASS_1  2
#define RENDER_VIEWID_RANGE1_PASS_2  3
#define RENDER_VIEWID_RANGE1_PASS_3  4
#define RENDER_VIEWID_RANGE1_PASS_4  5
#define RENDER_VIEWID_RANGE1_PASS_5  6
#define RENDER_VIEWID_RANGE5_PASS_6  7
#define RENDER_VIEWID_RANGE1_PASS_7 13

#define MAX_NUM_LIGHTS 5

struct PosNormalTexcoordVertex
{
    float    m_x;
    float    m_y;
    float    m_z;
    uint32_t m_normal;
    float    m_u;
    float    m_v;
};

static const float s_texcoord = 5.0f;
static PosNormalTexcoordVertex s_hplaneVertices[] =
{
    { -1.0f, 0.0f,  1.0f, encodeNormalRgba8(0.0f, 1.0f, 0.0f), s_texcoord, s_texcoord },
    {  1.0f, 0.0f,  1.0f, encodeNormalRgba8(0.0f, 1.0f, 0.0f), s_texcoord, 0.0f       },
    { -1.0f, 0.0f, -1.0f, encodeNormalRgba8(0.0f, 1.0f, 0.0f), 0.0f,       s_texcoord },
    {  1.0f, 0.0f, -1.0f, encodeNormalRgba8(0.0f, 1.0f, 0.0f), 0.0f,       0.0f       },
};

static PosNormalTexcoordVertex s_vplaneVertices[] =
{
    { -1.0f,  1.0f, 0.0f, encodeNormalRgba8(0.0f, 0.0f, -1.0f), 1.0f, 1.0f },
    {  1.0f,  1.0f, 0.0f, encodeNormalRgba8(0.0f, 0.0f, -1.0f), 1.0f, 0.0f },
    { -1.0f, -1.0f, 0.0f, encodeNormalRgba8(0.0f, 0.0f, -1.0f), 0.0f, 1.0f },
    {  1.0f, -1.0f, 0.0f, encodeNormalRgba8(0.0f, 0.0f, -1.0f), 0.0f, 0.0f },
};

static const PosNormalTexcoordVertex s_cubeVertices[] =
{
    { -1.0f,  1.0f,  1.0f, encodeNormalRgba8( 0.0f,  1.0f,  0.0f), 1.0f, 1.0f },
    {  1.0f,  1.0f,  1.0f, encodeNormalRgba8( 0.0f,  1.0f,  0.0f), 0.0f, 1.0f },
    { -1.0f,  1.0f, -1.0f, encodeNormalRgba8( 0.0f,  1.0f,  0.0f), 1.0f, 0.0f },
    {  1.0f,  1.0f, -1.0f, encodeNormalRgba8( 0.0f,  1.0f,  0.0f), 0.0f, 0.0f },
    { -1.0f, -1.0f,  1.0f, encodeNormalRgba8( 0.0f, -1.0f,  0.0f), 1.0f, 1.0f },
    {  1.0f, -1.0f,  1.0f, encodeNormalRgba8( 0.0f, -1.0f,  0.0f), 0.0f, 1.0f },
    { -1.0f, -1.0f, -1.0f, encodeNormalRgba8( 0.0f, -1.0f,  0.0f), 1.0f, 0.0f },
    {  1.0f, -1.0f, -1.0f, encodeNormalRgba8( 0.0f, -1.0f,  0.0f), 0.0f, 0.0f },
    {  1.0f, -1.0f,  1.0f, encodeNormalRgba8( 0.0f,  0.0f,  1.0f), 0.0f, 0.0f },
    {  1.0f,  1.0f,  1.0f, encodeNormalRgba8( 0.0f,  0.0f,  1.0f), 0.0f, 1.0f },
    { -1.0f, -1.0f,  1.0f, encodeNormalRgba8( 0.0f,  0.0f,  1.0f), 1.0f, 0.0f },
    { -1.0f,  1.0f,  1.0f, encodeNormalRgba8( 0.0f,  0.0f,  1.0f), 1.0f, 1.0f },
    {  1.0f, -1.0f, -1.0f, encodeNormalRgba8( 0.0f,  0.0f, -1.0f), 0.0f, 0.0f },
    {  1.0f,  1.0f, -1.0f, encodeNormalRgba8( 0.0f,  0.0f, -1.0f), 0.0f, 1.0f },
    { -1.0f, -1.0f, -1.0f, encodeNormalRgba8( 0.0f,  0.0f, -1.0f), 1.0f, 0.0f },
    { -1.0f,  1.0f, -1.0f, encodeNormalRgba8( 0.0f,  0.0f, -1.0f), 1.0f, 1.0f },
    {  1.0f,  1.0f, -1.0f, encodeNormalRgba8( 1.0f,  0.0f,  0.0f), 1.0f, 1.0f },
    {  1.0f,  1.0f,  1.0f, encodeNormalRgba8( 1.0f,  0.0f,  0.0f), 0.0f, 1.0f },
    {  1.0f, -1.0f, -1.0f, encodeNormalRgba8( 1.0f,  0.0f,  0.0f), 1.0f, 0.0f },
    {  1.0f, -1.0f,  1.0f, encodeNormalRgba8( 1.0f,  0.0f,  0.0f), 0.0f, 0.0f },
    { -1.0f,  1.0f, -1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 1.0f, 1.0f },
    { -1.0f,  1.0f,  1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0.0f, 1.0f },
    { -1.0f, -1.0f, -1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 1.0f, 0.0f },
    { -1.0f, -1.0f,  1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0.0f, 0.0f },
};

static const uint16_t s_cubeIndices[] =
{
    0,  1,  2,
    1,  3,  2,
    4,  6,  5,
    5,  6,  7,
    
    8,  9, 10,
    9, 11, 10,
    12, 14, 13,
    13, 14, 15,
    
    16, 17, 18,
    17, 19, 18,
    20, 22, 21,
    21, 22, 23,
};

static const uint16_t s_planeIndices[] =
{
    0, 1, 2,
    1, 3, 2,
};

static uint32_t s_viewMask = 0;
static uint32_t s_clearMask = 0;
static bgfx::UniformHandle s_texColor;

void setViewClearMask(uint32_t _viewMask, uint8_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
{
    for (uint32_t view = 0, viewMask = _viewMask; 0 != viewMask; viewMask >>= 1, view += 1 )
    {
        const uint32_t ntz = bx::uint32_cnttz(viewMask);
        viewMask >>= ntz;
        view += ntz;
        
        bgfx::setViewClear( (uint8_t)view, _flags, _rgba, _depth, _stencil);
    }
}

void setViewTransformMask(uint32_t _viewMask, const void* _view, const void* _proj)
{
    for (uint32_t view = 0, viewMask = _viewMask; 0 != viewMask; viewMask >>= 1, view += 1 )
    {
        const uint32_t ntz = bx::uint32_cnttz(viewMask);
        viewMask >>= ntz;
        view += ntz;
        
        bgfx::setViewTransform( (uint8_t)view, _view, _proj);
    }
}

void setViewRectMask(uint32_t _viewMask, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
{
    for (uint32_t view = 0, viewMask = _viewMask; 0 != viewMask; viewMask >>= 1, view += 1 )
    {
        const uint32_t ntz = bx::uint32_cnttz(viewMask);
        viewMask >>= ntz;
        view += ntz;
        
        bgfx::setViewRect( (uint8_t)view, _x, _y, _width, _height);
    }
}

void mtxReflected(float* _result, const bx::Vec3& _pos, const bx::Vec3& _normal)
{
    const float nx = _normal.x;
    const float ny = _normal.y;
    const float nz = _normal.z;
    
    _result[ 0] =  1.0f - 2.0f * nx * nx;
    _result[ 1] =       - 2.0f * nx * ny;
    _result[ 2] =       - 2.0f * nx * nz;
    _result[ 3] =  0.0f;
    
    _result[ 4] =       - 2.0f * nx * ny;
    _result[ 5] =  1.0f - 2.0f * ny * ny;
    _result[ 6] =       - 2.0f * ny * nz;
    _result[ 7] =  0.0f;
    
    _result[ 8] =       - 2.0f * nx * nz;
    _result[ 9] =       - 2.0f * ny * nz;
    _result[10] =  1.0f - 2.0f * nz * nz;
    _result[11] =  0.0f;
    
    const float dot = bx::dot(_pos, _normal);
    
    _result[12] =  2.0f * dot * nx;
    _result[13] =  2.0f * dot * ny;
    _result[14] =  2.0f * dot * nz;
    _result[15] =  1.0f;
}

void mtxShadow(float* _result, const float* _ground, const float* _light)
{
    const float dot =
    _ground[0] * _light[0]
    + _ground[1] * _light[1]
    + _ground[2] * _light[2]
    + _ground[3] * _light[3]
    ;
    
    _result[ 0] =  dot - _light[0] * _ground[0];
    _result[ 1] = 0.0f - _light[1] * _ground[0];
    _result[ 2] = 0.0f - _light[2] * _ground[0];
    _result[ 3] = 0.0f - _light[3] * _ground[0];
    
    _result[ 4] = 0.0f - _light[0] * _ground[1];
    _result[ 5] =  dot - _light[1] * _ground[1];
    _result[ 6] = 0.0f - _light[2] * _ground[1];
    _result[ 7] = 0.0f - _light[3] * _ground[1];
    
    _result[ 8] = 0.0f - _light[0] * _ground[2];
    _result[ 9] = 0.0f - _light[1] * _ground[2];
    _result[10] =  dot - _light[2] * _ground[2];
    _result[11] = 0.0f - _light[3] * _ground[2];
    
    _result[12] = 0.0f - _light[0] * _ground[3];
    _result[13] = 0.0f - _light[1] * _ground[3];
    _result[14] = 0.0f - _light[2] * _ground[3];
    _result[15] =  dot - _light[3] * _ground[3];
}

void mtxBillboard(float* _result, const float* _view, const float* _pos, const float* _scale)
{
    _result[ 0] = _view[0]  * _scale[0];
    _result[ 1] = _view[4]  * _scale[0];
    _result[ 2] = _view[8]  * _scale[0];
    _result[ 3] = 0.0f;
    _result[ 4] = _view[1]  * _scale[1];
    _result[ 5] = _view[5]  * _scale[1];
    _result[ 6] = _view[9]  * _scale[1];
    _result[ 7] = 0.0f;
    _result[ 8] = _view[2]  * _scale[2];
    _result[ 9] = _view[6]  * _scale[2];
    _result[10] = _view[10] * _scale[2];
    _result[11] = 0.0f;
    _result[12] = _pos[0];
    _result[13] = _pos[1];
    _result[14] = _pos[2];
    _result[15] = 1.0f;
}

struct Uniforms
{
    void init()
    {
        m_params.m_ambientPass   = 1.0f;
        m_params.m_lightingPass  = 1.0f;
        m_params.m_lightCount    = 4.0f;
        m_params.m_lightIndex    = 4.0f;
        
        m_ambient[0] = 0.02f;
        m_ambient[1] = 0.02f;
        m_ambient[2] = 0.02f;
        m_ambient[3] = 0.0f; //unused
        
        m_diffuse[0] = 0.2f;
        m_diffuse[1] = 0.2f;
        m_diffuse[2] = 0.2f;
        m_diffuse[3] = 0.0f; //unused
        
        m_specular_shininess[0] = 1.0f;
        m_specular_shininess[1] = 1.0f;
        m_specular_shininess[2] = 1.0f;
        m_specular_shininess[3] = 10.0f; //shininess
        
        m_color[0] = 1.0f;
        m_color[1] = 1.0f;
        m_color[2] = 1.0f;
        m_color[3] = 1.0f;
        
        m_time = 0.0f;
        
        for (uint8_t ii = 0; ii < MAX_NUM_LIGHTS; ++ii)
        {
            m_lightPosRadius[ii][0] = 0.0f;
            m_lightPosRadius[ii][1] = 0.0f;
            m_lightPosRadius[ii][2] = 0.0f;
            m_lightPosRadius[ii][3] = 1.0f;
            
            m_lightRgbInnerR[ii][0] = 1.0f;
            m_lightRgbInnerR[ii][1] = 1.0f;
            m_lightRgbInnerR[ii][2] = 1.0f;
            m_lightRgbInnerR[ii][3] = 1.0f;
        }
        
        u_params             = bgfx::createUniform("u_params",              bgfx::UniformType::Vec4);
        u_ambient            = bgfx::createUniform("u_ambient",             bgfx::UniformType::Vec4);
        u_diffuse            = bgfx::createUniform("u_diffuse",             bgfx::UniformType::Vec4);
        u_specular_shininess = bgfx::createUniform("u_specular_shininess",  bgfx::UniformType::Vec4);
        u_color              = bgfx::createUniform("u_color",               bgfx::UniformType::Vec4);
        u_lightPosRadius     = bgfx::createUniform("u_lightPosRadius",      bgfx::UniformType::Vec4, MAX_NUM_LIGHTS);
        u_lightRgbInnerR     = bgfx::createUniform("u_lightRgbInnerR",      bgfx::UniformType::Vec4, MAX_NUM_LIGHTS);
    }
    
    //call this once at initialization
    void submitConstUniforms()
    {
        bgfx::setUniform(u_ambient,            &m_ambient);
        bgfx::setUniform(u_diffuse,            &m_diffuse);
        bgfx::setUniform(u_specular_shininess, &m_specular_shininess);
    }
    
    //call this before each draw call
    void submitPerDrawUniforms()
    {
        bgfx::setUniform(u_params,         &m_params);
        bgfx::setUniform(u_color,          &m_color);
        bgfx::setUniform(u_lightPosRadius, &m_lightPosRadius, MAX_NUM_LIGHTS);
        bgfx::setUniform(u_lightRgbInnerR, &m_lightRgbInnerR, MAX_NUM_LIGHTS);
    }
    
    void destroy()
    {
        bgfx::destroy(u_params);
        bgfx::destroy(u_ambient);
        bgfx::destroy(u_diffuse);
        bgfx::destroy(u_specular_shininess);
        bgfx::destroy(u_color);
        bgfx::destroy(u_lightPosRadius);
        bgfx::destroy(u_lightRgbInnerR);
    }
    
    struct Params
    {
        float m_ambientPass;
        float m_lightingPass;
        float m_lightCount;
        float m_lightIndex;
    };
    
    struct SvParams
    {
        float m_useStencilTex;
        float m_dfail;
        float m_unused0;
        float m_unused1;
    };
    
    
    Params m_params;
    SvParams m_svparams;
    float m_ambient[4];
    float m_diffuse[4];
    float m_specular_shininess[4];
    float m_color[4];
    float m_time;
    float m_lightPosRadius[MAX_NUM_LIGHTS][4];
    float m_lightRgbInnerR[MAX_NUM_LIGHTS][4];
    
    /**
     * u_params.x - u_ambientPass
     * u_params.y - u_lightingPass
     * u_params.z - u_lightCount
     * u_params.w - u_lightIndex
     */
    bgfx::UniformHandle u_params;
    bgfx::UniformHandle u_ambient;
    bgfx::UniformHandle u_diffuse;
    bgfx::UniformHandle u_specular_shininess;
    bgfx::UniformHandle u_color;
    bgfx::UniformHandle u_lightPosRadius;
    bgfx::UniformHandle u_lightRgbInnerR;
};
static Uniforms s_uniforms;

struct ViewState
{
    ViewState(uint32_t _width = 0, uint32_t _height = 0)
    : m_width(_width)
    , m_height(_height)
    {
    }
    
    uint32_t m_width;
    uint32_t m_height;
    
    float m_view[16];
    float m_proj[16];
};

struct ClearValues
{
    ClearValues(uint32_t _clearRgba     = 0x30303000
                , float    _clearDepth    = 1.0f
                , uint8_t  _clearStencil  = 0
                )
    : m_clearRgba(_clearRgba)
    , m_clearDepth(_clearDepth)
    , m_clearStencil(_clearStencil)
    { }
    
    uint32_t m_clearRgba;
    float    m_clearDepth;
    uint8_t  m_clearStencil;
};

void clearView(bgfx::ViewId _id, uint8_t _flags, const ClearValues& _clearValues)
{
    bgfx::setViewClear(_id
                       , _flags
                       , _clearValues.m_clearRgba
                       , _clearValues.m_clearDepth
                       , _clearValues.m_clearStencil
                       );
    
    // Keep track of cleared views
    s_clearMask |= 1 << _id;
}

void clearViewMask(uint32_t _viewMask, uint8_t _flags, const ClearValues& _clearValues)
{
    setViewClearMask(_viewMask
                     , _flags
                     , _clearValues.m_clearRgba
                     , _clearValues.m_clearDepth
                     , _clearValues.m_clearStencil
                     );
    
    // Keep track of cleared views
    s_clearMask |= _viewMask;
}



bool stencil::init(void* nwh_)
{
    m_ready = true;
	m_width = WNDW_WIDTH;
	m_height = WNDW_HEIGHT;
	m_debug = BGFX_DEBUG_TEXT;
	m_reset = BGFX_RESET_VSYNC;

	bgfx::PlatformData pd;
	pd.nwh = nwh_;
	bgfx::setPlatformData(pd);

	bgfx::Init bgfxInit;
	bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
	bgfxInit.resolution.width = m_width;
	bgfxInit.resolution.height = m_height;
	bgfxInit.resolution.reset = m_reset;
	bgfx::init(bgfxInit);

	bgfx::setDebug(m_debug);

	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
		, 0x443355FF
		, 1.0f
		, 0
	);

	bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));
    
//    m_clearValues = ClearValues(0x30303000, 1.0f, 0);
    
    bgfx::VertexDecl pcvDecl;
    pcvDecl
    .begin()
    .add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
    .add(bgfx::Attrib::Normal,    4, bgfx::AttribType::Uint8, true, true)
    .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
    .end();
    
    m_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);

    m_ready &= sxb::Utils::loadProgram("vs_stencil_texture_lighting.bin", "fs_stencil_texture_lighting.bin", m_programTextureLighting);
    m_ready &= sxb::Utils::loadProgram("vs_stencil_color_lighting.bin", "fs_stencil_color_lighting.bin", m_programColorLighting);
    m_ready &= sxb::Utils::loadProgram("vs_stencil_color_texture.bin", "fs_stencil_color_texture.bin", m_programColorTexture);
    m_ready &= sxb::Utils::loadProgram("vs_stencil_color.bin", "fs_stencil_color_black.bin", m_programColorBlack);
    m_ready &= sxb::Utils::loadProgram("vs_stencil_texture.bin", "fs_stencil_texture.bin", m_programTexture);

    m_ready &= sxb::Utils::loadTexture("textures/figure-rgba.dds", m_figureTex);
    m_ready &= sxb::Utils::loadTexture("textures/flare.dds", m_flareTex);
    m_ready &= sxb::Utils::loadTexture("textures/fieldstone-rgba.dds", m_fieldstoneTex);

    m_bunnyMesh.load("meshes/bunny.bin");
    m_columnMesh.load("meshes/column.bin");
    m_cubeMesh.load(s_cubeVertices, BX_COUNTOF(s_cubeVertices), pcvDecl, s_cubeIndices, BX_COUNTOF(s_cubeIndices) );
    m_hplaneMesh.load(s_hplaneVertices, BX_COUNTOF(s_hplaneVertices), pcvDecl, s_planeIndices, BX_COUNTOF(s_planeIndices) );
    m_vplaneMesh.load(s_vplaneVertices, BX_COUNTOF(s_vplaneVertices), pcvDecl, s_planeIndices, BX_COUNTOF(s_planeIndices) );

	return m_ready;
}

void stencil::update(const uint64_t & frame_)
{
	if (m_ready)
	{
        // Floor position.
        float floorMtx[16];
        bx::mtxSRT(floorMtx
                   , 20.0f  //scaleX
                   , 20.0f  //scaleY
                   , 20.0f  //scaleZ
                   , 0.0f   //rotX
                   , 0.0f   //rotY
                   , 0.0f   //rotZ
                   , 0.0f   //translateX
                   , 0.0f   //translateY
                   , 0.0f   //translateZ
                   );
        
        // Bunny position.
        float bunnyMtx[16];
        bx::mtxSRT(bunnyMtx
                   , 5.0f
                   , 5.0f
                   , 5.0f
                   , 0.0f
                   , 1.56f - ((float)frame_ / 30)
                   , 0.0f
                   , 0.0f
                   , 2.0f
                   , 0.0f
                   );
        
        // Columns position.
        const float dist = 14.0f;
        const float columnPositions[4][3] =
        {
            {  dist, 0.0f,  dist },
            { -dist, 0.0f,  dist },
            {  dist, 0.0f, -dist },
            { -dist, 0.0f, -dist },
        };
        
        float columnMtx[4][16];
        for (uint8_t ii = 0; ii < 4; ++ii)
        {
            bx::mtxSRT(columnMtx[ii]
                       , 1.0f
                       , 1.0f
                       , 1.0f
                       , 0.0f
                       , 0.0f
                       , 0.0f
                       , columnPositions[ii][0]
                       , columnPositions[ii][1]
                       , columnPositions[ii][2]
                       );
        }
        
        const uint8_t numCubes = 9;
        float cubeMtx[numCubes][16];
        for (uint16_t ii = 0; ii < numCubes; ++ii)
        {
            bx::mtxSRT(cubeMtx[ii]
                       , 1.0f
                       , 1.0f
                       , 1.0f
                       , 0.0f
                       , 0.0f
                       , 0.0f
                       , bx::sin(ii * 2.0f + 13.0f - ((float)frame_ / 30)) * 13.0f
                       , 4.0f
                       , bx::cos(ii * 2.0f + 13.0f - ((float)frame_ / 30)) * 13.0f
                       );
        }
        
        // Make sure at the beginning everything gets cleared.
//        clearView(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, m_clearValues);
        bgfx::touch(0);
//        sxb::s_viewMask |= 1;
        sxb::Utils::getMem(m_residentMem, m_virtualMem);
        
        bgfx::dbgTextPrintf(0, 5, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 7, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 5, 0x0f, "%d", frame_);
        bgfx::dbgTextPrintf(0, 7, 0x0f, "mem(resident,virtual): (%.3fm, %.3fm)", m_residentMem, m_virtualMem);

		const bx::Vec3 at = { 0.0f,  0.0f,  0.0f };
		const bx::Vec3 eye = { 10.0f,  10.0f,  -30.0f };

		{
			float view[16];
			bx::mtxLookAt(view, eye, at);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
			bgfx::setViewTransform(0, view, proj);
		}
        
        // Floor.
//        m_hplaneMesh.submit(0
//                            , m_programColorBlack
//                            , floorMtx
//                            , sxb::s_renderStates[sxb::RenderState::StencilReflection_BlendPlane]
//                            , m_texColor
//                            );
        

        
        // Compute reflected matrix.
        float reflectMtx[16];
        mtxReflected(reflectMtx, { 0.0f, 0.01f, 0.0f }, { 0.0f, 1.0f, 0.0f });
        
        // Reflect and submit bunny.
        float mtxReflectedBunny[16];
        bx::mtxMul(mtxReflectedBunny, bunnyMtx, reflectMtx);
        m_bunnyMesh.submit(0
                           , m_programColorLighting
                           , mtxReflectedBunny
                           , sxb::s_renderStates[sxb::RenderState::StencilReflection_DrawReflected]
                           , m_texColor
                           );
        
        // Reflect and submit columns.
        float mtxReflectedColumn[16];
        for (uint8_t ii = 0; ii < 4; ++ii)
        {
            bx::mtxMul(mtxReflectedColumn, columnMtx[ii], reflectMtx);
            m_columnMesh.submit(0
                                , m_programColorLighting
                                , mtxReflectedColumn
                                , BGFX_STATE_DEFAULT
                                );
        }
        
		m_bunnyMesh.submit(0, m_programColorLighting, bunnyMtx, BGFX_STATE_DEFAULT);
        
        // Columns.
        for (uint8_t ii = 0; ii < 4; ++ii)
        {
            m_columnMesh.submit(0
                                , m_programColorLighting
                                , columnMtx[ii]
                                , BGFX_STATE_DEFAULT
                                );
        }

		bgfx::frame();
	}
}
