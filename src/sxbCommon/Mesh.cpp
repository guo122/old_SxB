
#include <bx/bx.h>
#include <bx/file.h>
#include <bx/sort.h>
#include <bgfx/bgfx.h>
#include <bgfx/dbg.h>
#include <bx/readerwriter.h>
#include <bx/filepath.h>
#include <bx/bxstring.h>
#include <ib-compress/indexbufferdecompression.h>
#include <bgfx/vertexdecl.h>
#include "sxbCommon/utils.h"
#include "sxbCommon/Mesh.h"

SXB_NAMESPACE_BEGIN

bool Mesh::load(const char* _filePath)
{
	bool Result = false;
	bx::FileReaderI* reader = getFileReader();
	if (bx::open(reader, _filePath))
	{
		Result = loadImpl(reader);
		bx::close(reader);
	}

	return Result;
}

bool Mesh::load(
	const void* _vertices,
	uint32_t _numVertices,
	const ::bgfx::VertexDecl& _decl,
	const void* _indices,
	uint32_t _numIndices
)
{
	bool Result = true;
	Group group;
	group.m_vbh = bgfx::createVertexBuffer(bgfx::makeRef(_vertices, _numVertices), _decl);
	group.m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(_indices, _numIndices));

	m_groups.push_back(group);
	group.reset();

	return Result;
}

void Mesh::unload()
{
	for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
	{
		const Group& group = *it;
		::bgfx::destroy(group.m_vbh);

		if (::bgfx::isValid(group.m_ibh))
		{
			::bgfx::destroy(group.m_ibh);
		}
	}
	m_groups.clear();
}

void Mesh::submit(::bgfx::ViewId _id, ::bgfx::ProgramHandle _program, const float* _mtx, uint64_t _state) const
{
	if (BGFX_STATE_MASK == _state)
	{
		_state = 0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_DEPTH_TEST_LESS
			| BGFX_STATE_CULL_CCW
			| BGFX_STATE_MSAA
			;
	}

	::bgfx::setTransform(_mtx);
	::bgfx::setState(_state);

	for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
	{
		const Group& group = *it;

		::bgfx::setIndexBuffer(group.m_ibh);
		::bgfx::setVertexBuffer(0, group.m_vbh);
		::bgfx::submit(_id, _program, 0, it != itEnd - 1);
	}
}

void Mesh::submit(MeshState _state[], uint8_t _numPasses, const float* _mtx, uint16_t _numMatrices) const
{
	uint32_t cached = ::bgfx::setTransform(_mtx, _numMatrices);

	for (uint32_t pass = 0; pass < _numPasses; ++pass)
	{
		::bgfx::setTransform(cached, _numMatrices);

		const MeshState& state = _state[pass];
		::bgfx::setState(state.m_state);

		for (uint8_t tex = 0; tex < state.m_numTextures; ++tex)
		{
			const MeshState::Texture& texture = state.m_textures[tex];
			::bgfx::setTexture(texture.m_stage
				, texture.m_sampler
				, texture.m_texture
				, texture.m_flags
			);
		}

		for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
		{
			const Group& group = *it;

			::bgfx::setIndexBuffer(group.m_ibh);
			::bgfx::setVertexBuffer(0, group.m_vbh);
			::bgfx::submit(state.m_viewId, state.m_program, 0, it != itEnd - 1);
		}
	}
}


void Mesh::submit(bgfx::ViewId _id, bgfx::ProgramHandle _program, float* _mtx, const RenderState& _renderState, bgfx::UniformHandle _uniform, Uniforms &uxu_) const
{
    bgfx::TextureHandle texture = BGFX_INVALID_HANDLE;
    submit(_id, _program, _mtx, _renderState, texture, _uniform, uxu_);
}

void Mesh::submit(bgfx::ViewId _id, bgfx::ProgramHandle _program, float* _mtx, const RenderState& _renderState, bgfx::TextureHandle _texture, const bgfx::UniformHandle &_uniform, Uniforms &uxu_) const
{
    for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
    {
        const Group& group = *it;
        
        // Set uniforms
        uxu_.submitPerDrawUniforms();
        
        // Set model matrix for rendering.
        bgfx::setTransform(_mtx);
        bgfx::setIndexBuffer(group.m_ibh);
        bgfx::setVertexBuffer(0, group.m_vbh);
        
        // Set texture
        bgfx::setTexture(0, _uniform, _texture);
        
        // Apply render state
        bgfx::setStencil(_renderState.m_fstencil, _renderState.m_bstencil);
        bgfx::setState(_renderState.m_state, _renderState.m_blendFactorRgba);
        
        // Submit
        bgfx::submit(_id, _program);
    }
}

bool Mesh::loadImpl(bx::ReaderSeekerI* _reader)
{
	bool Result = true;
#define BGFX_CHUNK_MAGIC_VB  BX_MAKEFOURCC('V', 'B', ' ', 0x1)
#define BGFX_CHUNK_MAGIC_IB  BX_MAKEFOURCC('I', 'B', ' ', 0x0)
#define BGFX_CHUNK_MAGIC_IBC BX_MAKEFOURCC('I', 'B', 'C', 0x0)
#define BGFX_CHUNK_MAGIC_PRI BX_MAKEFOURCC('P', 'R', 'I', 0x0)

	using namespace bx;
	using namespace bgfx;

	Group group;

	bx::AllocatorI* allocator = getAllocator();

	uint32_t chunk;
	bx::Error err;
	while (4 == bx::read(_reader, chunk, &err)
		&& err.isOk())
	{
		switch (chunk)
		{
		case BGFX_CHUNK_MAGIC_VB:
		{
			read(_reader, group.m_sphere);
			read(_reader, group.m_aabb);
			read(_reader, group.m_obb);

			read(_reader, m_decl);

			uint16_t stride = m_decl.getStride();

			uint16_t numVertices;
			read(_reader, numVertices);
			const ::bgfx::Memory* mem = ::bgfx::alloc(numVertices*stride);
			read(_reader, mem->data, mem->size);

			group.m_vbh = ::bgfx::createVertexBuffer(mem, m_decl);
		}
		break;

		case BGFX_CHUNK_MAGIC_IB:
		{
			uint32_t numIndices;
			read(_reader, numIndices);
			const ::bgfx::Memory* mem = ::bgfx::alloc(numIndices * 2);
			read(_reader, mem->data, mem->size);
			group.m_ibh = ::bgfx::createIndexBuffer(mem);
		}
		break;

		case BGFX_CHUNK_MAGIC_IBC:
		{
			uint32_t numIndices;
			bx::read(_reader, numIndices);

			const ::bgfx::Memory* mem = ::bgfx::alloc(numIndices * 2);

			uint32_t compressedSize;
			bx::read(_reader, compressedSize);

			void* compressedIndices = BX_ALLOC(allocator, compressedSize);

			bx::read(_reader, compressedIndices, compressedSize);

			ReadBitstream rbs((const uint8_t*)compressedIndices, compressedSize);
			DecompressIndexBuffer((uint16_t*)mem->data, numIndices / 3, rbs);

			BX_FREE(allocator, compressedIndices);

			group.m_ibh = ::bgfx::createIndexBuffer(mem);
		}
		break;

		case BGFX_CHUNK_MAGIC_PRI:
		{
			uint16_t len;
			read(_reader, len);

			stl::string material;
			material.resize(len);
			read(_reader, const_cast<char*>(material.c_str()), len);

			uint16_t num;
			read(_reader, num);

			for (uint32_t ii = 0; ii < num; ++ii)
			{
				read(_reader, len);

				stl::string name;
				name.resize(len);
				read(_reader, const_cast<char*>(name.c_str()), len);

				Primitive prim;
				read(_reader, prim.m_startIndex);
				read(_reader, prim.m_numIndices);
				read(_reader, prim.m_startVertex);
				read(_reader, prim.m_numVertices);
				read(_reader, prim.m_sphere);
				read(_reader, prim.m_aabb);
				read(_reader, prim.m_obb);

				group.m_prims.push_back(prim);
			}

			m_groups.push_back(group);
			group.reset();
		}
		break;

		default:
			DBG("%08x at %d", chunk, bx::skip(_reader, 0));
			break;
		}
	}

	return Result;
}

MeshState* meshStateCreate()
{
	MeshState* state = (MeshState*)BX_ALLOC(getAllocator(), sizeof(MeshState) );
	return state;
}

void meshStateDestroy(MeshState* _meshState)
{
	BX_FREE(getAllocator(), _meshState);
}

SXB_NAMESPACE_END
