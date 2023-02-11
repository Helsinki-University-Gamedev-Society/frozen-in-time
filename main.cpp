#include "ui/ui.hpp"
#include "ui/ui_elements.hpp"
#include <SDL_ttf.h>

int main(int argc, char *argv[])
{
    auto ctx = init_graphics();

    UI ui = UI(ctx);

    bool quit = false;

    while(not quit) {
	ui.update(); // Update UI

	UIEvent event;
	while(ui.poll(&event)) { // Keep polling events until there are no more
	    if(event.type == UIEvent_Type::EXIT) {
		quit = true;
	    }
	}

	ui.render(); // Render game

	SDL_Delay(10); // Sleep to give CPU a break
    }


    return 0;
}
