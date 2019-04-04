
#ifndef LOD_H_DC8C8E2F5FF1CD11F91286184C879E21
#define LOD_H_DC8C8E2F5FF1CD11F91286184C879E21

#include <stdint.h>  // int32_t

#include <bgfx/bgfx.h>

#include <sxbTop/defines.h>

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

struct KnightPos
{
	int32_t m_x;
	int32_t m_y;
};

static const KnightPos knightTour[8 * 4] =
{
	{0,0}, {1,2}, {3,3}, {4,1}, {5,3}, {7,2}, {6,0}, {5,2},
	{7,3}, {6,1}, {4,0}, {3,2}, {2,0}, {0,1}, {1,3}, {2,1},
	{0,2}, {1,0}, {2,2}, {0,3}, {1,1}, {3,0}, {4,2}, {5,0},
	{7,1}, {6,3}, {5,1}, {7,0}, {6,2}, {4,3}, {3,1}, {2,3},
};

class lod
{
public:
	lod(): m_ready(false) {};
	~lod() {};

public:
	bool init(void* nwh_);

	void update(const uint64_t & frame_ = 0);

private:
	bool m_ready;
	bgfx::ProgramHandle m_program;
};

#endif // LOD_H_DC8C8E2F5FF1CD11F91286184C879E21