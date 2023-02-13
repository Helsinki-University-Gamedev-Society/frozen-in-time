#include <iostream>

#include <SDL_filesystem.h>
#include <SDL_ttf.h>

#include "ui/ui.hpp"
#include "ui/ui_elements.hpp"
#include "utils/file_access.hpp"

int main(int argc, char *argv[])
{
    auto ctx = init_graphics();

    UI ui = UI(ctx);

    bool quit = false;

    while(not quit) {
	ui.update(); // Update UI

	UIEvent event;
	while(ui.poll(&event)) { // Keep polling events until there are no more
	    if(UIEvent_of_type<UIEvent_EXIT>(event)) {
		quit = true;
	    } else if(UIEvent_of_type<UIEvent_SEND_COMMAND>(event)) {
		UIEvent_SEND_COMMAND command_event = std::get<UIEvent_SEND_COMMAND>(event);
		if(command_event.command == "eat banana") {
		    ui.write(command_event.story, "Nom nom nom! What a great banana that was!!!");
		    ui.set_map_image("world_map.png");
		}
	    }
	}

	ui.render(); // Render UI
    }


    return 0;
}
