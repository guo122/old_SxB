
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/math.h>
#include <bx/readerwriter.h>
#include <sxbCommon/utils.h>
#include "cube.h"

bool Cube::init(void* nwh_)
{
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

	m_ready = sxb::Utils::loadProgram("vs_stencil_color_lighting.bin", "fs_stencil_color_lighting.bin", m_program);

	m_bunnyMesh = sxb::meshLoad("meshes/bunny.bin");

	return m_ready;
}

void Cube::update(const uint64_t & frame_)
{
	if (m_ready)
	{
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

		bgfx::touch(0);

		bgfx::dbgTextPrintf(0, 1, 0x0f, "(%d, %d)", m_mouseX, m_mouseX);
		bgfx::dbgTextPrintf(0, 3, 0x0f, m_dbgText.c_str());

		const bx::Vec3 at = { 0.0f,  0.0f,  0.0f };
		const bx::Vec3 eye = { 10.0f,  10.0f,  -30.0f };

		{
			float view[16];
			bx::mtxLookAt(view, eye, at);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
			bgfx::setViewTransform(0, view, proj);
		}

		sxb::meshSubmit(m_bunnyMesh, 0, m_program, bunnyMtx, BGFX_STATE_DEFAULT);

		bgfx::frame();
	}
}