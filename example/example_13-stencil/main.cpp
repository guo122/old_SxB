
#include <SFML/Config.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Event.hpp>

#include <sxbCommon/utils.h>
#include "stencil.h"

#if defined(SXB_SYSTEM_IOS)
#include <SFML/Main.hpp>
#endif

int main(int argc, char *argv[])
 {
     // Create the main window
     sf::WindowBase window(sf::VideoMode(WNDW_WIDTH, WNDW_HEIGHT), "SFML window");
	 stencil exampleStencil;
	 exampleStencil.init(window.getWindowHandle());

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
             else if (event.type == sf::Event::TouchBegan && event.touch.finger == 0)
                 exampleStencil.touchBegin(event.touch.x, event.touch.y);
             else if (event.type == sf::Event::TouchMoved && event.touch.finger == 0)
                 exampleStencil.setCursor(event.touch.x, event.touch.y);
             else if (event.type == sf::Event::MouseButtonPressed)
                 exampleStencil.setCursor(event.mouseMove.x, event.mouseMove.y);
         }

		 exampleStencil.update(count);
		 count++;
     }

     return EXIT_SUCCESS;
 }
