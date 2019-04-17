
#ifndef MESH_H_717850E498228FA76EE08CEABF44B4A9
#define MESH_H_717850E498228FA76EE08CEABF44B4A9

#include <tinystl/allocator.h>
#include <tinystl/vector.h>
#include <tinystl/string.h>
namespace stl = tinystl;

#include "sxbCommon/defines.h"

SXB_NAMESPACE_BEGIN


#define RENDER_VIEWID_RANGE1_PASS_0  1
#define RENDER_VIEWID_RANGE1_PASS_1  2
#define RENDER_VIEWID_RANGE1_PASS_2  3
#define RENDER_VIEWID_RANGE1_PASS_3  4
#define RENDER_VIEWID_RANGE1_PASS_4  5
#define RENDER_VIEWID_RANGE1_PASS_5  6
#define RENDER_VIEWID_RANGE5_PASS_6  7
#define RENDER_VIEWID_RANGE1_PASS_7 13

#define MAX_NUM_LIGHTS 5

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

struct RenderState
{
    enum Enum
    {
        StencilReflection_CraftStencil = 0,
        StencilReflection_DrawReflected,
        StencilReflection_BlendPlane,
        StencilReflection_DrawScene,
        
        ProjectionShadows_DrawAmbient,
        ProjectionShadows_CraftStencil,
        ProjectionShadows_DrawDiffuse,
        
        Custom_BlendLightTexture,
        Custom_DrawPlaneBottom,
        
        Count
    };
    
    uint64_t m_state;
    uint32_t m_blendFactorRgba;
    uint32_t m_fstencil;
    uint32_t m_bstencil;
};

static RenderState s_renderStates[RenderState::Count] =
{
    { // StencilReflection_CraftStencil
        BGFX_STATE_WRITE_RGB
        | BGFX_STATE_WRITE_Z
        | BGFX_STATE_DEPTH_TEST_LESS
        | BGFX_STATE_MSAA
        , UINT32_MAX
        , BGFX_STENCIL_TEST_ALWAYS         // pass always
        | BGFX_STENCIL_FUNC_REF(1)         // value = 1
        | BGFX_STENCIL_FUNC_RMASK(0xff)
        | BGFX_STENCIL_OP_FAIL_S_REPLACE
        | BGFX_STENCIL_OP_FAIL_Z_REPLACE
        | BGFX_STENCIL_OP_PASS_Z_REPLACE   // store the value
        , BGFX_STENCIL_NONE
    },
    { // StencilReflection_DrawReflected
        BGFX_STATE_WRITE_RGB
        | BGFX_STATE_WRITE_A
        | BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
        | BGFX_STATE_WRITE_Z
        | BGFX_STATE_DEPTH_TEST_LESS
        | BGFX_STATE_CULL_CW    //reflection matrix has inverted normals. using CCW instead of CW.
        | BGFX_STATE_MSAA
        , UINT32_MAX
        , BGFX_STENCIL_TEST_EQUAL
        | BGFX_STENCIL_FUNC_REF(1)
        | BGFX_STENCIL_FUNC_RMASK(1)
        | BGFX_STENCIL_OP_FAIL_S_KEEP
        | BGFX_STENCIL_OP_FAIL_Z_KEEP
        | BGFX_STENCIL_OP_PASS_Z_KEEP
        , BGFX_STENCIL_NONE
    },
    { // StencilReflection_BlendPlane
        BGFX_STATE_WRITE_RGB
        | BGFX_STATE_WRITE_Z
        | BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_SRC_COLOR)
        | BGFX_STATE_DEPTH_TEST_LESS
        | BGFX_STATE_CULL_CCW
        | BGFX_STATE_MSAA
        , UINT32_MAX
        , BGFX_STENCIL_NONE
        , BGFX_STENCIL_NONE
    },
    { // StencilReflection_DrawScene
        BGFX_STATE_WRITE_RGB
        | BGFX_STATE_WRITE_Z
        | BGFX_STATE_DEPTH_TEST_LESS
        | BGFX_STATE_CULL_CCW
        | BGFX_STATE_MSAA
        , UINT32_MAX
        , BGFX_STENCIL_NONE
        , BGFX_STENCIL_NONE
    },
    { // ProjectionShadows_DrawAmbient
        BGFX_STATE_WRITE_RGB
        | BGFX_STATE_WRITE_Z // write depth !
        | BGFX_STATE_DEPTH_TEST_LESS
        | BGFX_STATE_CULL_CCW
        | BGFX_STATE_MSAA
        , UINT32_MAX
        , BGFX_STENCIL_NONE
        , BGFX_STENCIL_NONE
    },
    { // ProjectionShadows_CraftStencil
        BGFX_STATE_DEPTH_TEST_LESS
        | BGFX_STATE_MSAA
        , UINT32_MAX
        , BGFX_STENCIL_TEST_ALWAYS         // pass always
        | BGFX_STENCIL_FUNC_REF(1)         // value = 1
        | BGFX_STENCIL_FUNC_RMASK(0xff)
        | BGFX_STENCIL_OP_FAIL_S_KEEP
        | BGFX_STENCIL_OP_FAIL_Z_KEEP
        | BGFX_STENCIL_OP_PASS_Z_REPLACE   // store the value
        , BGFX_STENCIL_NONE
    },
    { // ProjectionShadows_DrawDiffuse
        BGFX_STATE_WRITE_RGB
        | BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE)
        | BGFX_STATE_DEPTH_TEST_EQUAL
        | BGFX_STATE_CULL_CCW
        | BGFX_STATE_MSAA
        , UINT32_MAX
        , BGFX_STENCIL_TEST_NOTEQUAL
        | BGFX_STENCIL_FUNC_REF(1)
        | BGFX_STENCIL_FUNC_RMASK(1)
        | BGFX_STENCIL_OP_FAIL_S_KEEP
        | BGFX_STENCIL_OP_FAIL_Z_KEEP
        | BGFX_STENCIL_OP_PASS_Z_KEEP
        , BGFX_STENCIL_NONE
    },
    { // Custom_BlendLightTexture
        BGFX_STATE_WRITE_RGB
        | BGFX_STATE_WRITE_A
        | BGFX_STATE_WRITE_Z
        | BGFX_STATE_DEPTH_TEST_LESS
        | BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_COLOR, BGFX_STATE_BLEND_INV_SRC_COLOR)
        | BGFX_STATE_CULL_CCW
        | BGFX_STATE_MSAA
        , UINT32_MAX
        , BGFX_STENCIL_NONE
        , BGFX_STENCIL_NONE
    },
    { // Custom_DrawPlaneBottom
        BGFX_STATE_WRITE_RGB
        | BGFX_STATE_CULL_CW
        | BGFX_STATE_MSAA
        , UINT32_MAX
        , BGFX_STENCIL_NONE
        , BGFX_STENCIL_NONE
    },
};


///
struct MeshState
{
	struct Texture
	{
		uint32_t            m_flags;
		::bgfx::UniformHandle m_sampler;
		::bgfx::TextureHandle m_texture;
		uint8_t             m_stage;
	};

	Texture             m_textures[4];
	uint64_t            m_state;
	::bgfx::ProgramHandle m_program;
	uint8_t             m_numTextures;
	::bgfx::ViewId        m_viewId;
};


struct Aabb
{
	float m_min[3];
	float m_max[3];
};

struct Obb
{
	float m_mtx[16];
};

struct Sphere
{
	float m_center[3];
	float m_radius;
};

struct Primitive
{
	uint32_t m_startIndex;
	uint32_t m_numIndices;
	uint32_t m_startVertex;
	uint32_t m_numVertices;

	Sphere m_sphere;
	Aabb m_aabb;
	Obb m_obb;
};

typedef stl::vector<Primitive> PrimitiveArray;

struct Group
{
	Group()
	{
		reset();
	}

	void reset()
	{
		m_vbh.idx = ::bgfx::kInvalidHandle;
		m_ibh.idx = ::bgfx::kInvalidHandle;
		m_prims.clear();
	}

	::bgfx::VertexBufferHandle m_vbh;
	::bgfx::IndexBufferHandle m_ibh;
	Sphere m_sphere;
	Aabb m_aabb;
	Obb m_obb;
	PrimitiveArray m_prims;
};


class Mesh
{
public:
	Mesh() {}
	~Mesh() {}

public:
	bool load(const char* _filePath);

	bool load(
		const void* _vertices,
		uint32_t _numVertices,
		const ::bgfx::VertexDecl& _decl,
		const void* _indices,
		uint32_t _numIndices
	);

	void unload();

	void submit(::bgfx::ViewId _id, ::bgfx::ProgramHandle _program, const float* _mtx, uint64_t _state) const;

	void submit(MeshState _state[], uint8_t _numPasses, const float* _mtx, uint16_t _numMatrices) const;
    
    void submit(bgfx::ViewId _id, bgfx::ProgramHandle _program, float* _mtx, const RenderState& _renderState, bgfx::UniformHandle _uniform, Uniforms &uxu_) const;
    
    void submit(bgfx::ViewId _id, bgfx::ProgramHandle _program, float* _mtx, const RenderState& _renderState, bgfx::TextureHandle _texture, const bgfx::UniformHandle &_uniform, Uniforms &uxu_) const;

private:
	bool loadImpl(bx::ReaderSeekerI* _reader);

private:
	::bgfx::VertexDecl m_decl;
	typedef stl::vector<Group> GroupArray;
	GroupArray m_groups;
};

///
MeshState* meshStateCreate();

///
void meshStateDestroy(MeshState* _meshState);

SXB_NAMESPACE_END

#endif // MESH_H_717850E498228FA76EE08CEABF44B4A9
