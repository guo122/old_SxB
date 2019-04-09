
#ifndef MESH_H_717850E498228FA76EE08CEABF44B4A9
#define MESH_H_717850E498228FA76EE08CEABF44B4A9

#include <tinystl/allocator.h>
#include <tinystl/vector.h>
#include <tinystl/string.h>
namespace stl = tinystl;

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