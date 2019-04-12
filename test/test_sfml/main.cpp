

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>

#include <SFML/Window/WindowBase.hpp>
#include <SFML/Config.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window/Event.hpp>

#define SC_WIDTH 1334
#define SC_HEIGHT 750

int main(int argc, char * argv[]) {

    bgfx::init();
    // Create the main window
    sf::WindowBase window(sf::VideoMode(SC_WIDTH, SC_HEIGHT), "SFML window", sf::Style::None);
//
//    bgfx::PlatformData pd;
//    pd.nwh = window.getSystemHandle();
//    bgfx::setPlatformData(pd);
//
//    bgfx::Init bgfxInit;
//    bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
//    bgfxInit.resolution.width = SC_WIDTH;
//    bgfxInit.resolution.height = SC_HEIGHT;
//    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
//    bgfx::init(bgfxInit);
//
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

    }

    return 0;
}
