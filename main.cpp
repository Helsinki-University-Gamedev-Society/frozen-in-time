#include <iostream>

#include <SDL_filesystem.h>
#include <SDL_ttf.h>

#include "game/cparser.hpp"

#include "game/game.hpp"
#include "ui/ui.hpp"
#include "ui/ui_elements.hpp"
#include "utils/file_access.hpp"

int main(int argc, char *argv[])
{
    UI ui = init_UI();
    Game game = Game(&ui);

    bool quit = false;

    ui.play_music("paulstretched-uncertainty.ogg");
    ui.set_map_image("map_digsite.png");

    game.ChangeScene(Scene::TENT);

    while(not quit) {
    	ui.update(); // Update UI

    	UIEvent event;
    	while(ui.poll(&event)) { // Keep polling events until there are no more
    	    if(UIEvent_of_type<UIEvent_EXIT>(event)) {
    		quit = true;
    	    } else if(UIEvent_of_type<UIEvent_SEND_COMMAND>(event)) {
    		UIEvent_SEND_COMMAND command_event = std::get<UIEvent_SEND_COMMAND>(event);
		game.Execute(command_event.story, command_event.command);
    	    }
    	}

    	ui.render(); // Render UI
    }

    return 0;
}
