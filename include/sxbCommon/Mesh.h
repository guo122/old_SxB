
#ifndef MESH_H_717850E498228FA76EE08CEABF44B4A9
#define MESH_H_717850E498228FA76EE08CEABF44B4A9

#include "sxbTop/defines.h"

SXB_NAMESPACE_BEGIN

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

struct Mesh;

///
Mesh* meshLoad(const char* _filePath);

///
void meshUnload(Mesh* _mesh);

///
MeshState* meshStateCreate();

///
void meshStateDestroy(MeshState* _meshState);

///
void meshSubmit(const Mesh* _mesh, ::bgfx::ViewId _id, ::bgfx::ProgramHandle _program, const float* _mtx, uint64_t _state = BGFX_STATE_MASK);

///
void meshSubmit(const Mesh* _mesh, const MeshState*const* _state, uint8_t _numPasses, const float* _mtx, uint16_t _numMatrices = 1);


SXB_NAMESPACE_END

#endif // MESH_H_717850E498228FA76EE08CEABF44B4A9