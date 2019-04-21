
#include <SFML/Config.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Event.hpp>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>

#include <sxbCommon/defines.h>
#include <sxbCommon/utils.h>

#include "logo.h"

#if defined(SXB_SYSTEM_IOS)
#include <SFML/Main.hpp>
#endif

#define CUR_WIDTH       1136
#define CUR_HEIGHT      640

#define MAX_FINGER      5

struct v2
{
    v2():key(false),x(0),y(0){}
    bool key;
    int x;
    int y;
};

// Please set platform data window to a CAMetalLayer
int main(int argc, char *argv[])
{
    // Create the main window
    sf::WindowBase window(sf::VideoMode(CUR_WIDTH, CUR_HEIGHT), "SFML window");
    
    bgfx::PlatformData pd;
    pd.nwh = window.getWindowHandle();
    bgfx::setPlatformData(pd);
    
    bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
    bgfxInit.resolution.width = CUR_WIDTH;
    bgfxInit.resolution.height = CUR_HEIGHT;
    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
    bgfx::init(bgfxInit);
    
    bgfx::setDebug(BGFX_DEBUG_TEXT);
    
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, CUR_WIDTH, CUR_HEIGHT);
    
    uint64_t count = 0;
    v2 touch[MAX_FINGER];
    
    v2 resize;
    
    double residentMem = 0;
    double virtualMem = 0;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::TouchBegan)
            {
                if (event.touch.finger < MAX_FINGER)
                    touch[event.touch.finger].key = true;
            }
            else if (event.type == sf::Event::TouchMoved)
            {
                if (event.touch.finger < MAX_FINGER)
                {
                    touch[event.touch.finger].x = event.touch.x;
                    touch[event.touch.finger].y = event.touch.y;
                }
            }
            else if (event.type == sf::Event::TouchEnded)
            {
                if (event.touch.finger < MAX_FINGER)
                    touch[event.touch.finger].key = false;
            }
            else if (event.type == sf::Event::Resized)
                resize.x = event.size.width, resize.y = event.size.height;
        }
        
        sxb::Utils::getMem(residentMem, virtualMem);
        
        resize.x = window.getSize().x;
        resize.y = window.getSize().y;
        
        bgfx::touch(0);
        
        // Use debug font to print information about this example.
        bgfx::dbgTextClear();
        bgfx::dbgTextImage(
                           bx::max<uint16_t>(uint16_t(CUR_WIDTH / 2 / 8), 20) - 20
                           , bx::max<uint16_t>(uint16_t(CUR_HEIGHT / 2 / 16), 6) - 6
                           , 40
                           , 12
                           , s_logo
                           , 160
                           );
        bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
        
        bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
        bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
        
        bgfx::dbgTextPrintf(0, 5, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 7, 0x0f, "                                    ");
        bgfx::dbgTextPrintf(0, 9, 0x0f, "                                    ");
        
        bgfx::dbgTextPrintf(0, 5, 0x0f, "%d", count);
        bgfx::dbgTextPrintf(0, 7, 0x0f, "resize: (%d, %d)", resize.x, resize.y);
        bgfx::dbgTextPrintf(0, 9, 0x0f, "mem(resident,virtual): (%.3fm, %.3fm)", residentMem, virtualMem);
        
        for (int i = 0; i < MAX_FINGER; ++i) {
            bgfx::dbgTextPrintf(0, 11 + i, 0x0f, "                                    ");
            if (touch[i].key)
                bgfx::dbgTextPrintf(0, 11 + i, 0x0f, "\x1b[14;mtouch%d: (%d, %d)\x1b[0m", i, touch[i].x, touch[i].y);
            else
                bgfx::dbgTextPrintf(0, 11 + i, 0x0f, "touch%d: (%d, %d)", i, touch[i].x, touch[i].y);
        }
        
        const bgfx::Stats* stats = bgfx::getStats();
        bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters."
                            , stats->width
                            , stats->height
                            , stats->textWidth
                            , stats->textHeight
                            );
        
        bgfx::frame();
        count++;
    }
    
    return EXIT_SUCCESS;
}
