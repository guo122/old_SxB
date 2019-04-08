
#include <SFML/Config.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Event.hpp>
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/math.h>

#include <sxbCommon/utils.h>
#include "lod.h"

int main(int argc, char *argv[])
 {
     // Create the main window
     sf::WindowBase window(sf::VideoMode(WNDW_WIDTH, WNDW_HEIGHT), "SFML window");
	 lod exampleLod;
	 exampleLod.init(window.getSystemHandle());

	 uint64_t count = 0;

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
         }

		 exampleLod.update(count);
		 count++;
     }

     return EXIT_SUCCESS;
 }