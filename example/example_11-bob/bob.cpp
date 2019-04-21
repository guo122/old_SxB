
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/math.h>
#include <bx/readerwriter.h>
#include <sxbCommon/utils.h>
#include "bob.h"

struct NormalBackgroundVertex
{
    float m_x;
    float m_y;
    float m_z;
    uint32_t m_abgr;
    
    static void init()
    {
        ms_decl
        .begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
        .end();
    };
    
    static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl NormalBackgroundVertex::ms_decl;

static NormalBackgroundVertex s_mountainVertices[] =
{
    {-20.0f,  0.0f,  10.0f, 0xff00ff00 },
    {-15.0f,  7.0f,  10.0f, 0xff00ff00 },
    {-10.0f,  3.0f,  10.0f, 0xff00ff00 },
    {0.0f,  15.0f,  10.0f, 0xff00ff00 },
    {7.0f,  0.0f,  10.0f, 0xff00ff00 },
};

static const uint16_t s_mountainList[] =
{
    0, 1,
    1, 2,
    2, 3,
    3, 4,
};


bool Bob::init(void* nwh_)
{
    m_ready = true;
	m_width = WNDW_WIDTH;
	m_height = WNDW_HEIGHT;
	m_debug = BGFX_DEBUG_TEXT;
	m_reset = BGFX_RESET_VSYNC;
    
    NormalBackgroundVertex::init();

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

	m_ready &= sxb::Utils::loadProgram("vs_cubes.bin", "fs_cubes.bin", m_program);
    m_ready &= m_bunnyMesh.load("meshes/bunny.bin");
    m_ready &= m_mountainMesh.load(s_mountainVertices, sizeof(s_mountainVertices), NormalBackgroundVertex::ms_decl, s_mountainList, sizeof(s_mountainList));

	return m_ready;
}

void Bob::update(const uint64_t & frame_)
{
	if (m_ready)
	{
		bgfx::touch(0);
        //m_sceneTime = (float)(frame_ % 270) / 10;
        if (m_delta.x > 30 && m_delta.x <= 60)
        {
            m_pos.x += 1;
        }
        else if (m_delta.x > 60 && m_delta.x <= 100)
        {
            m_pos.x += 2;
        }
        else if (m_delta.x > 100 && m_delta.x <= 200)
        {
            
            m_pos.x += 3;
        }
        else if (m_delta.x > 200)
        {
            
            m_pos.x += 6;
        }
        else if (m_delta.x < -30)
        {
            m_pos.x -= 1;
        }
        m_sceneTime = (float)(m_pos.x % 270) / 10;
        sxb::Utils::getMem(m_residentMem, m_virtualMem);
        float mountainMtx[16];
        
        // Bunny position.
        float bunnyMtx[16];
        bx::mtxSRT(bunnyMtx
                   , 5.0f
                   , 5.0f
                   , 5.0f
                   , 0.0f
                   , 1.56f
                   , 0.0f
                   , 0.0f
                   , -2.0f
                   , 0.0f
                   );

		const bx::Vec3 at = { 0.0f, 5.0f,      0.0f };
		const bx::Vec3 eye = { 0.0f, 0.0f,  -20.0f };

		{
			float view[16];
			bx::mtxLookAt(view, eye, at);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
			bgfx::setViewTransform(0, view, proj);
		}
        
        bgfx::dbgTextPrintf(0, 5, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 7, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 9, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 11, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 5, 0x0f, "%d, %.3f", frame_, m_sceneTime);
        bgfx::dbgTextPrintf(0, 7, 0x0f, "mem(resident,virtual): (%.3fm, %.3fm)", m_residentMem, m_virtualMem);

        
        for (int i = 0; i < 5; ++i) {
            
            bx::mtxSRT(mountainMtx
                       , 1.0f
                       , 1.0f
                       , 1.0f
                       , 0.0f
                       , 0.0f
                       , 0.0f
                       , -10.0f + ((float)i * 27) - m_sceneTime
                       , 0.0f + 7.0f
                       , 0.0f
                       );
            m_mountainMesh.submit(0, m_program, mountainMtx, BGFX_STATE_DEFAULT | BGFX_STATE_PT_LINES);
            
            bx::mtxSRT(mountainMtx
                       , 1.0f
                       , 0.5f
                       , 1.0f
                       , 0.0f
                       , 0.0f
                       , 0.0f
                       , -10.0f + ((float)i * 27) - (m_sceneTime * 2)
                       , 0.0f
                       , 0.0f
                       );
            m_mountainMesh.submit(0, m_program, mountainMtx, BGFX_STATE_DEFAULT | BGFX_STATE_PT_LINES);
        }
        
        m_bunnyMesh.submit(0, m_program, bunnyMtx, BGFX_STATE_DEFAULT);
        
		bgfx::frame();
	}
}
