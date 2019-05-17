
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/math.h>
#include <bx/readerwriter.h>

#include <sxbCommon/utils.h>
#include "ibl.h"

struct PosColorTexCoord0Vertex
{
    float m_x;
    float m_y;
    float m_z;
    uint32_t m_rgba;
    float m_u;
    float m_v;
    
    static void init()
    {
        ms_decl
        .begin()
        .add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
        .end();
    }
    
    static bgfx::VertexDecl ms_decl;
};
//
bgfx::VertexDecl PosColorTexCoord0Vertex::ms_decl;
//
void screenSpaceQuad(float _textureWidth, float _textureHeight, bool _originBottomLeft = false, float _width = 1.0f, float _height = 1.0f)
{
    if (3 == bgfx::getAvailTransientVertexBuffer(3, PosColorTexCoord0Vertex::ms_decl) )
    {
        bgfx::TransientVertexBuffer vb;
        bgfx::allocTransientVertexBuffer(&vb, 3, PosColorTexCoord0Vertex::ms_decl);
        PosColorTexCoord0Vertex* vertex = (PosColorTexCoord0Vertex*)vb.data;
        
        const float zz = 0.0f;
        
        const float minx = -_width;
        const float maxx =  _width;
        const float miny = 0.0f;
        const float maxy = _height*2.0f;
        
        const float texelHalfW = s_texelHalf/_textureWidth;
        const float texelHalfH = s_texelHalf/_textureHeight;
        const float minu = -1.0f + texelHalfW;
        const float maxu =  1.0f + texelHalfW;
        
        float minv = texelHalfH;
        float maxv = 2.0f + texelHalfH;
        
        if (_originBottomLeft)
        {
            std::swap(minv, maxv);
            minv -= 1.0f;
            maxv -= 1.0f;
        }
        
        vertex[0].m_x = minx;
        vertex[0].m_y = miny;
        vertex[0].m_z = zz;
        vertex[0].m_rgba = 0xffffffff;
        vertex[0].m_u = minu;
        vertex[0].m_v = minv;
        
        vertex[1].m_x = maxx;
        vertex[1].m_y = miny;
        vertex[1].m_z = zz;
        vertex[1].m_rgba = 0xffffffff;
        vertex[1].m_u = maxu;
        vertex[1].m_v = minv;
        
        vertex[2].m_x = maxx;
        vertex[2].m_y = maxy;
        vertex[2].m_z = zz;
        vertex[2].m_rgba = 0xffffffff;
        vertex[2].m_u = maxu;
        vertex[2].m_v = maxv;
        
        bgfx::setVertexBuffer(0, &vb);
    }
}

#pragma mark -

bool ibl::init(void* nwh_)
{
    m_ready = true;
    m_width = 1366;
    m_height = 768;
    m_debug = BGFX_DEBUG_TEXT;
    m_reset  = 0
    | BGFX_RESET_VSYNC
    | BGFX_RESET_MSAA_X16
    ;
    
    bgfx::PlatformData pd;
    pd.nwh = nwh_;
    bgfx::setPlatformData(pd);
    
    bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
    bgfxInit.resolution.width = m_width;
    bgfxInit.resolution.height = m_height;
    bgfxInit.resolution.reset = m_reset;
    bgfx::init(bgfxInit);

    // Enable debug text.
    bgfx::setDebug(m_debug);
    
    // Set views  clear state.
    bgfx::setViewClear(0
                       , BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
                       , 0x303030ff
                       , 1.0f
                       , 0
                       );
    
    // Uniforms.
    m_uniforms.init();
    
    // Vertex declarations.
    PosColorTexCoord0Vertex::init();
    
    m_lightProbes[LightProbe::Bolonga].load("bolonga");
    m_lightProbes[LightProbe::Kyoto  ].load("kyoto");
    m_currentLightProbe = LightProbe::Bolonga;
    
    u_mtx        = bgfx::createUniform("u_mtx",        bgfx::UniformType::Mat4);
    u_params     = bgfx::createUniform("u_params",     bgfx::UniformType::Vec4);
    u_flags      = bgfx::createUniform("u_flags",      bgfx::UniformType::Vec4);
    u_camPos     = bgfx::createUniform("u_camPos",     bgfx::UniformType::Vec4);
    s_texCube    = bgfx::createUniform("s_texCube",    bgfx::UniformType::Sampler);
    s_texCubeIrr = bgfx::createUniform("s_texCubeIrr", bgfx::UniformType::Sampler);
    
    m_ready &= sxb::Utils::loadProgram("vs_ibl_mesh.bin", "fs_ibl_mesh.bin", m_programMesh);
    m_ready &= sxb::Utils::loadProgram("vs_ibl_skybox.bin", "fs_ibl_skybox.bin", m_programSky);
    
    m_meshBunny.load("meshes/bunny.bin");
    m_meshOrb.load("meshes/orb.bin");
    
	return m_ready;
}

void ibl::update(const uint64_t & frame_)
{
	if (m_ready)
	{
        m_uniforms.m_glossiness   = m_settings.m_glossiness;
        m_uniforms.m_reflectivity = m_settings.m_reflectivity;
        m_uniforms.m_exposure     = m_settings.m_exposure;
        m_uniforms.m_bgType       = m_settings.m_bgType;
        m_uniforms.m_metalOrSpec   = float(m_settings.m_metalOrSpec);
        m_uniforms.m_doDiffuse     = float(m_settings.m_doDiffuse);
        m_uniforms.m_doSpecular    = float(m_settings.m_doSpecular);
        m_uniforms.m_doDiffuseIbl  = float(m_settings.m_doDiffuseIbl);
        m_uniforms.m_doSpecularIbl = float(m_settings.m_doSpecularIbl);
        bx::memCopy(m_uniforms.m_rgbDiff,  m_settings.m_rgbDiff,  3*sizeof(float) );
        bx::memCopy(m_uniforms.m_rgbSpec,  m_settings.m_rgbSpec,  3*sizeof(float) );
        bx::memCopy(m_uniforms.m_lightDir, m_settings.m_lightDir, 3*sizeof(float) );
        bx::memCopy(m_uniforms.m_lightCol, m_settings.m_lightCol, 3*sizeof(float) );
        
        int64_t now = bx::getHPCounter();
        static int64_t last = now;
        const int64_t frameTime = now - last;
        last = now;
        const double freq = double(bx::getHPFrequency() );
        const float deltaTimeSec = float(double(frameTime)/freq);
        
        bgfx::dbgTextPrintf(0, 5, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 7, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 9, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 11, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 13, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 5, 0x0f, "%d", frame_);
//        bgfx::dbgTextPrintf(0, 7, 0x0f, "mem(resident,virtual): (%.3fm, %.3fm)", m_residentMem, m_virtualMem);
//        bgfx::dbgTextPrintf(0, 9, 0x0f, "eye: (%.3f, %.3f, %.3f)", m_eye.x, m_eye.y, m_eye.z);
//        bgfx::dbgTextPrintf(0, 11, 0x0f, "touch: (%i, %i)", m_touch_x, m_touch_y );
//        bgfx::dbgTextPrintf(0, 13, 0x0f, "del: (%i, %i)", m_delta_x, m_delta_y );
        
        // Camera.
//        const bool mouseOverGui = ImGui::MouseOverArea();
//        m_mouse.update(float(m_mouseState.m_mx), float(m_mouseState.m_my), m_mouseState.m_mz, m_width, m_height);
//        if (!mouseOverGui)
//        {
//            if (m_mouseState.m_buttons[entry::MouseButton::Left])
//            {
//                m_camera.orbit(m_mouse.m_dx, m_mouse.m_dy);
//            }
//            else if (m_mouseState.m_buttons[entry::MouseButton::Right])
//            {
//                m_camera.dolly(m_mouse.m_dx + m_mouse.m_dy);
//            }
//            else if (m_mouseState.m_buttons[entry::MouseButton::Middle])
//            {
//                m_settings.m_envRotDest += m_mouse.m_dx*2.0f;
//            }
//            else if (0 != m_mouse.m_scroll)
//            {
//                m_camera.dolly(float(m_mouse.m_scroll)*0.05f);
//            }
//        }
        if (m_touch[2].press)
        {
            // middle
            m_settings.m_envRotDest += (float)m_touch[2].deltaX / 300.0;
        }
        else if (m_touch[1].press)
        {
            // right
            m_camera.dolly((float)m_touch[1].deltaX / 300.0 + (float)m_touch[1].deltaY / 300.0);
        }
        else
        {
            // left
            m_camera.orbit(-(float)m_touch[0].deltaX / 300.0, (float)m_touch[0].deltaY / 300.0);
        }

        m_camera.update(deltaTimeSec);
        bx::memCopy(m_uniforms.m_cameraPos, &m_camera.m_pos.curr.x, 3*sizeof(float) );
        
        // View Transform 0.
        float view[16];
        bx::mtxIdentity(view);
        
        const bgfx::Caps* caps = bgfx::getCaps();
        
        float proj[16];
        bx::mtxOrtho(proj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f, 0.0, caps->homogeneousDepth);
        bgfx::setViewTransform(0, view, proj);
        
        // View Transform 1.
        m_camera.mtxLookAt(view);
        bx::mtxProj(proj, 45.0f, float(m_width)/float(m_height), 0.1f, 100.0f, caps->homogeneousDepth);
        bgfx::setViewTransform(1, view, proj);
        
        // View rect.
        bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
        bgfx::setViewRect(1, 0, 0, uint16_t(m_width), uint16_t(m_height) );
        
        // Env rotation.
        const float amount = bx::min(deltaTimeSec/0.12f, 1.0f);
        m_settings.m_envRotCurr = bx::lerp(m_settings.m_envRotCurr, m_settings.m_envRotDest, amount);
//        m_settings.m_envRotCurr = 3.19999957;
//        m_settings.m_envRotDest = 3.19999909;
        
        // Env mtx.
        float mtxEnvView[16];
        m_camera.envViewMtx(mtxEnvView);
        float mtxEnvRot[16];
        bx::mtxRotateY(mtxEnvRot, m_settings.m_envRotCurr);
        bx::mtxMul(m_uniforms.m_mtx, mtxEnvView, mtxEnvRot); // Used for Skybox.
        
        // Submit view 0.
        bgfx::setTexture(0, s_texCube, m_lightProbes[m_currentLightProbe].m_tex);
        bgfx::setTexture(1, s_texCubeIrr, m_lightProbes[m_currentLightProbe].m_texIrr);
        bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
        screenSpaceQuad( (float)m_width, (float)m_height, true);
        m_uniforms.submit();
        bgfx::submit(0, m_programSky);
        
        // Submit view 1.
        bx::memCopy(m_uniforms.m_mtx, mtxEnvRot, 16*sizeof(float)); // Used for IBL.
        if (0 == m_settings.m_meshSelection)
        {
            // Submit bunny.
            float mtx[16];
            bx::mtxSRT(mtx, 1.0f, 1.0f, 1.0f, 0.0f, bx::kPi, 0.0f, 0.0f, -0.80f, 0.0f);
            bgfx::setTexture(0, s_texCube,    m_lightProbes[m_currentLightProbe].m_tex);
            bgfx::setTexture(1, s_texCubeIrr, m_lightProbes[m_currentLightProbe].m_texIrr);
            m_uniforms.submit();
            m_meshBunny.submit(1, m_programMesh, mtx, BGFX_STATE_MASK);
//            meshSubmit(m_meshBunny, 1, m_programMesh, mtx);
        }
        else
        {
            // Submit orbs.
            for (float yy = 0, yend = 5.0f; yy < yend; yy+=1.0f)
            {
                for (float xx = 0, xend = 5.0f; xx < xend; xx+=1.0f)
                {
                    const float scale   =  1.2f;
                    const float spacing =  2.2f;
                    const float yAdj    = -0.8f;
                    
                    float mtx[16];
                    bx::mtxSRT(mtx
                               , scale/xend
                               , scale/xend
                               , scale/xend
                               , 0.0f
                               , 0.0f
                               , 0.0f
                               , 0.0f      + (xx/xend)*spacing - (1.0f + (scale-1.0f)*0.5f - 1.0f/xend)
                               , yAdj/yend + (yy/yend)*spacing - (1.0f + (scale-1.0f)*0.5f - 1.0f/yend)
                               , 0.0f
                               );
                    
                    m_uniforms.m_glossiness   =        xx*(1.0f/xend);
                    m_uniforms.m_reflectivity = (yend-yy)*(1.0f/yend);
                    m_uniforms.m_metalOrSpec = 0.0f;
                    m_uniforms.submit();
                    
                    bgfx::setTexture(0, s_texCube,    m_lightProbes[m_currentLightProbe].m_tex);
                    bgfx::setTexture(1, s_texCubeIrr, m_lightProbes[m_currentLightProbe].m_texIrr);
                    m_meshOrb.submit(1, m_programMesh, mtx, BGFX_STATE_MASK);
//                    meshSubmit(m_meshOrb, 1, m_programMesh, mtx);
                }
            }
        }
        
        // Advance to next frame. Rendering thread will be kicked to
        // process submitted rendering primitives.
        bgfx::frame();
	}
}
