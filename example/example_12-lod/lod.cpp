
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/math.h>
#include <bx/readerwriter.h>
#include <sxbCommon/utils.h>
#include "lod.h"

bool lod::init(void* nwh_)
{
	m_width = WNDW_WIDTH;
	m_height = WNDW_HEIGHT;
	m_debug = BGFX_DEBUG_NONE;
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
		, 0x303030ff
		, 1.0f
		, 0
	);

	bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

	s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
	s_texStipple = bgfx::createUniform("s_texStipple", bgfx::UniformType::Sampler);
	u_stipple = bgfx::createUniform("u_stipple", bgfx::UniformType::Vec4);

	m_ready = sxb::Utils::loadProgram("vs_tree.bin", "fs_tree.bin", m_program);
 
	m_ready &= sxb::Utils::loadTexture("textures/leafs1.dds", m_textureLeafs);
	m_ready &= sxb::Utils::loadTexture("textures/bark1.dds", m_textureBark);

	const bgfx::Memory* stippleTex = bgfx::alloc(8 * 4);
	bx::memSet(stippleTex->data, 0, stippleTex->size);

	for (uint8_t ii = 0; ii < 32; ++ii)
	{
		stippleTex->data[knightTour[ii].m_y * 8 + knightTour[ii].m_x] = ii * 4;
	}

	m_textureStipple = bgfx::createTexture2D(8, 4, false, 1
		, bgfx::TextureFormat::R8
		, BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_MIN_POINT
		, stippleTex
	);

	m_meshTop[0].load("meshes/tree1b_lod0_1.bin");
	m_meshTop[1].load("meshes/tree1b_lod1_1.bin");
	m_meshTop[2].load("meshes/tree1b_lod2_1.bin");

	m_meshTrunk[0].load("meshes/tree1b_lod0_2.bin");
	m_meshTrunk[1].load("meshes/tree1b_lod1_2.bin");
	m_meshTrunk[2].load("meshes/tree1b_lod2_2.bin");

	m_scrollArea = 0;
	m_transitions = true;

	m_transitionFrame = 0;
	m_currLod = 0;
	m_targetLod = 0;

	m_distance = 2.0f;

	return m_ready;
}

void lod::update(const uint64_t & frame_)
{
	if (m_ready)
	{
		bgfx::touch(0);

		const bx::Vec3 at = { 0.0f, 1.0f,      0.0f };
		const bx::Vec3 eye = { 0.0f, 2.0f, -m_distance };

		{
			float view[16];
			bx::mtxLookAt(view, eye, at);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
			bgfx::setViewTransform(0, view, proj);
		}

		float mtx[16];
		bx::mtxScale(mtx, 0.1f, 0.1f, 0.1f);

		float stipple[3];
		float stippleInv[3];

		const int currentLODframe = m_transitions ? 32 - m_transitionFrame : 32;
		const int mainLOD = m_transitions ? m_currLod : m_targetLod;

		stipple[0] = 0.0f;
		stipple[1] = -1.0f;
		stipple[2] = (float(currentLODframe)*4.0f / 255.0f) - (1.0f / 255.0f);

		stippleInv[0] = (float(31)*4.0f / 255.0f);
		stippleInv[1] = 1.0f;
		stippleInv[2] = (float(m_transitionFrame)*4.0f / 255.0f) - (1.0f / 255.0f);

		const uint64_t stateTransparent = 0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_DEPTH_TEST_LESS
			| BGFX_STATE_CULL_CCW
			| BGFX_STATE_MSAA
			| BGFX_STATE_BLEND_ALPHA
			;

		const uint64_t stateOpaque = BGFX_STATE_DEFAULT;

		bgfx::setTexture(0, s_texColor, m_textureBark);
		bgfx::setTexture(1, s_texStipple, m_textureStipple);
		bgfx::setUniform(u_stipple, stipple);
		m_meshTrunk[mainLOD].submit(0, m_program, mtx, stateOpaque);

		bgfx::setTexture(0, s_texColor, m_textureLeafs);
		bgfx::setTexture(1, s_texStipple, m_textureStipple);
		bgfx::setUniform(u_stipple, stipple);
		m_meshTop[mainLOD].submit(0, m_program, mtx, stateTransparent);

		if (m_transitions
			&& (m_transitionFrame != 0))
		{
			bgfx::setTexture(0, s_texColor, m_textureBark);
			bgfx::setTexture(1, s_texStipple, m_textureStipple);
			bgfx::setUniform(u_stipple, stippleInv);
			m_meshTrunk[m_targetLod].submit(0, m_program, mtx, stateOpaque);

			bgfx::setTexture(0, s_texColor, m_textureLeafs);
			bgfx::setTexture(1, s_texStipple, m_textureStipple);
			bgfx::setUniform(u_stipple, stippleInv);
			m_meshTop[m_targetLod].submit(0, m_program, mtx, stateTransparent);
		}

		int lod = 0;
		if (eye.z < -2.5f)
		{
			lod = 1;
		}

		if (eye.z < -5.0f)
		{
			lod = 2;
		}

		if (m_targetLod != lod)
		{
			if (m_targetLod == m_currLod)
			{
				m_targetLod = lod;
			}
		}

		if (m_currLod != m_targetLod)
		{
			m_transitionFrame++;
		}

		if (m_transitionFrame > 32)
		{
			m_currLod = m_targetLod;
			m_transitionFrame = 0;
		}

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}
}