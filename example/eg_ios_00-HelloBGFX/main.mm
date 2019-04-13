
#include <SFML/Config.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Main.hpp>

#include "cube.h"

int main(int argc, char *argv[])
 {
     // Create the main window
     sf::WindowBase window(sf::VideoMode(WNDW_WIDTH, WNDW_HEIGHT), "SFML window");

	 Cube exampleCube;
	 exampleCube.init(window.getSystemHandle());

	 uint64_t counter = 0;

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

		 exampleCube.update(counter);
		 counter++;
     }

     return EXIT_SUCCESS;
 }
