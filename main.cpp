#include "ui/ui.hpp"

int main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
	printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	return 1;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
	printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	return 1;
    }

    UI ui = UI();

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
