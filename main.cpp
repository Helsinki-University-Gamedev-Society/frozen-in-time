#include <iostream>

#include <SDL_filesystem.h>
#include <SDL_ttf.h>

#include "game/cparser.hpp"

#include "ui/ui.hpp"
#include "ui/ui_elements.hpp"
#include "utils/file_access.hpp"

int main(int argc, char *argv[])
{
    UI ui = init_UI();

    bool quit = false;

    ui.play_music("paulstretched-uncertainty.ogg");

    while(not quit) {
    	ui.update(); // Update UI

    	UIEvent event;
    	while(ui.poll(&event)) { // Keep polling events until there are no more
    	    if(UIEvent_of_type<UIEvent_EXIT>(event)) {
    		quit = true;
    	    } else if(UIEvent_of_type<UIEvent_SEND_COMMAND>(event)) {
    		UIEvent_SEND_COMMAND command_event = std::get<UIEvent_SEND_COMMAND>(event);
    		if(command_event.command == "eat banana") {
    		    ui.add_inventory_item("item_pickaxe.png");
    		    ui.write(command_event.story, "Nom nom nom! What a great banana that was!!!");
    		    ui.set_map_image("world_map.png");
    		} else if(command_event.command == "uneat banana") {
    		    ui.remove_inventory_item("item_pickaxe.png");
    		    ui.write(command_event.story, "Blegh! Banana successfully regurgitated!");
    		    ui.set_map_image("world_map_present.png");
    		}
    	    }
    	}

    	ui.render(); // Render UI
    }

    return 0;
}
