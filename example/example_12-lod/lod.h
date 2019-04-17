
#ifndef LOD_H_DC8C8E2F5FF1CD11F91286184C879E21
#define LOD_H_DC8C8E2F5FF1CD11F91286184C879E21

#include <stdint.h>  // int32_t

#include <bgfx/bgfx.h>
#include <bgfx/bgfx_utils.h>

#include <sxbCommon/defines.h>
#include <sxbCommon/Mesh.h>

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
	~lod() 
	{
		// Cleanup.
		//bgfx::destroy(m_program);

		bgfx::destroy(s_texColor);
		bgfx::destroy(s_texStipple);
		bgfx::destroy(u_stipple);

		bgfx::destroy(m_textureStipple);
		bgfx::destroy(m_textureLeafs);
		bgfx::destroy(m_textureBark);

		// Shutdown bgfx.
		bgfx::shutdown();
	};

public:
	bool init(void* nwh_);

	void update(const uint64_t & frame_ = 0);

private:
	bool m_ready;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	sxb::Mesh m_meshTop[3];
	sxb::Mesh m_meshTrunk[3];

	bgfx::ProgramHandle m_program;
	bgfx::UniformHandle s_texColor;
	bgfx::UniformHandle s_texStipple;
	bgfx::UniformHandle u_stipple;

	bgfx::TextureHandle m_textureStipple;
	bgfx::TextureHandle m_textureLeafs;
	bgfx::TextureHandle m_textureBark;

	int32_t m_scrollArea;
	int32_t m_transitionFrame;
	int32_t m_currLod;
	int32_t m_targetLod;
	bool    m_transitions;
	float m_distance;
};

#endif // LOD_H_DC8C8E2F5FF1CD11F91286184C879E21
