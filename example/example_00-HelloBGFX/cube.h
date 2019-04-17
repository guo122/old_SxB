
#ifndef CUBE_H_2AA8FDAF22E7C21931959563A005530C
#define CUBE_H_2AA8FDAF22E7C21931959563A005530C

#include <bgfx/bgfx.h>
#include <bx/uint32_t.h>

#include <sxbCommon/defines.h>

struct PosColorVertex
{
	float x;
	float y;
	float z;
	uint32_t abgr;
};

static PosColorVertex cubeVertices[] =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t cubeTriList[] =
{
	0, 1, 2,
	1, 3, 2,
	4, 6, 5,
	5, 6, 7,
	0, 2, 4,
	4, 2, 6,
	1, 5, 3,
	5, 7, 3,
	0, 4, 1,
	4, 5, 1,
	2, 3, 6,
	6, 3, 7,
};

class Cube
{
public:
	Cube() : m_ready(false) {};
	~Cube() 
	{
		bgfx::destroy(m_program);

		bgfx::destroy(m_vbh);
		bgfx::destroy(m_ibh);

		bgfx::shutdown();
	};

public:
	bool init(void* nwh_);

	void update(const uint64_t & frame_ = 0);

private:
	bool m_ready;
	bgfx::ProgramHandle m_program;
	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
    double m_residentMem;
    double m_virtualMem;
};

#endif // CUBE_H_2AA8FDAF22E7C21931959563A005530C
