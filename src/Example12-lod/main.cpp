
#include <Config.hpp>
#include <Window/WindowBase.hpp>
#include <Window/Event.hpp>
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/math.h>

#include <sxbCommon/utils.h>
#include "lod.h"

int main(int argc, char *argv[])
 {
     // Create the main window
     tinySFML::WindowBase window(tinySFML::VideoMode(WNDW_WIDTH, WNDW_HEIGHT), "SFML window");
	 lod *exampleLod = new lod;
	 exampleLod->init( window.getSystemHandle() );

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

		 const bx::Vec3 at = { 0.0f, 0.0f,  0.0f };
		 const bx::Vec3 eye = { 0.0f, 0.0f, -5.0f };
		 float view[16];
		 bx::mtxLookAt(view, eye, at);

		 float proj[16];
		 bx::mtxProj(proj, 60.0f, float(WNDW_WIDTH) / float(WNDW_HEIGHT), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
		 bgfx::setViewTransform(0, view, proj);

		 exampleLod->update();

		 bgfx::frame();
     }

     return EXIT_SUCCESS;
 }