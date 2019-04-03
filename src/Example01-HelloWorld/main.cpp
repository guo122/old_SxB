
#include <Config.hpp>
#include <Window/WindowBase.hpp>
#include <Window/Event.hpp>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>

#include "logo.h"

#define		WNDW_WIDTH		800
#define		WNDW_HEIGHT		600

int main(int argc, char *argv[])
 {
     // Create the main window
     tinySFML::WindowBase window(tinySFML::VideoMode(WNDW_WIDTH, WNDW_HEIGHT), "SFML window");

	 bgfx::PlatformData pd;
	 pd.nwh = window.getSystemHandle();
	 bgfx::setPlatformData(pd);

	 bgfx::Init bgfxInit;
	 bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
	 bgfxInit.resolution.width = WNDW_WIDTH;
	 bgfxInit.resolution.height = WNDW_HEIGHT;
	 bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
	 bgfx::init(bgfxInit);

	 bgfx::setDebug(BGFX_DEBUG_TEXT);

	 bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
	 bgfx::setViewRect(0, 0, 0, WNDW_WIDTH, WNDW_HEIGHT);

     // Start the game loop
     while (window.isOpen())
     {
         // Process events
		 tinySFML::Event event;
         while (window.pollEvent(event))
         {
             // Close window: exit
             if (event.type == tinySFML::Event::Closed)
                 window.close();
         }

		 bgfx::touch(0);

		 // Use debug font to print information about this example.
		 bgfx::dbgTextClear();
		 bgfx::dbgTextImage(
			 bx::max<uint16_t>(uint16_t(WNDW_WIDTH / 2 / 8), 20) - 20
			 , bx::max<uint16_t>(uint16_t(WNDW_HEIGHT / 2 / 16), 6) - 6
			 , 40
			 , 12
			 , s_logo
			 , 160
		 );
		 bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");

		 bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
		 bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");

		 const bgfx::Stats* stats = bgfx::getStats();
		 bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters."
			 , stats->width
			 , stats->height
			 , stats->textWidth
			 , stats->textHeight
		 );

		 bgfx::frame();
     }

     return EXIT_SUCCESS;
 }