
#include <SFML/Config.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Event.hpp>
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/math.h>

#include <sxbCommon/utils.h>
#include "cube.h"

int main(int argc, char *argv[])
 {
     // Create the main window
     sf::WindowBase window(sf::VideoMode(WNDW_WIDTH, WNDW_HEIGHT), "SFML window");
	 Cube cube;
	 cube.init(window.getSystemHandle());

	 uint64_t count = 0;

     // Start the game loop
     while (window.isOpen())
     {
         // Process events
		 sf::Event event;
		 while (window.pollEvent(event))
		 {
			 switch (event.type)
			 {
			 case sf::Event::MouseButtonPressed: {
				 cube.mousePressed();
			 } break;
			 case sf::Event::MouseButtonReleased: {
				 cube.mouseRelease();
			 } break;
			 case sf::Event::MouseMoved: {
				 cube.setMouse(event.mouseMove.x, event.mouseMove.y);
			 } break;
			 case sf::Event::KeyPressed: {
					cube.setKey(event.key.code);
			 } break;
			 case sf::Event::Closed: window.close(); break;
			 default:break;
			 }
		 }
		 cube.update(count);
		 count++;
         //printf("%d\n", bgfx::getRendererType());
     }

     return EXIT_SUCCESS;
 }
