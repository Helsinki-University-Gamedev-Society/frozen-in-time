#include <SDL_keyboard.h>
#include <algorithm>
#include <iostream>
#include <memory>

#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>

#include "ui/animations.hpp"
#include "ui/assets.hpp"
#include "ui/ui.hpp"
#include "ui/ui_elements.hpp"

GraphicsContext::GraphicsContext()
    : window(SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0))
    , renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))
    , assets(AssetManager(renderer)) {}

void GraphicsContext::play_sound(string sound) {
    Mix_PlayChannel(-1, assets.get_sound(sound), 0);
}

void GraphicsContext::play_sound(Sound sound) {
    Mix_PlayChannel(-1, assets.get_sound(sound), 0);
}

shared_ptr<GraphicsContext> init_graphics() {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
	printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
	printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }

    if(TTF_Init() == -1) {
	printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }

    return std::make_shared<GraphicsContext>();
}

SDL_Rect GraphicsContext::game_viewport() {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    int game_width = std::min(width, 16 * height / 9);
    int game_height = game_width * 9 / 16;

    int top_left_x = (width - game_width) / 2;
    int top_left_y = (height - game_height) / 2;

    return SDL_Rect{top_left_x, top_left_y, game_width, game_height};
}

SDL_Rect GraphicsContext::viewport_from_layout(SDL_Rect layout) {
    SDL_Rect game_rect = game_viewport();
	
    double scale = ((double) game_rect.w) / ((double) LAYOUT_BACKGROUND.w);

    return SDL_Rect{
	(int) (game_rect.x + layout.x * scale),
	(int) (game_rect.y + layout.y * scale),
	(int) (layout.w * scale),
	(int) (layout.h * scale),
    };
}

int GraphicsContext::width_from_layout_width(int layout_width) {
    SDL_Rect game_rect = game_viewport();

    double scale = ((double) game_rect.w) / ((double) LAYOUT_BACKGROUND.w);

    return (int) (layout_width * scale);
}

UI::UI(shared_ptr<GraphicsContext> ctx)
    : ctx(ctx)
    , inventory(UIInventory(ctx))
    , map(UIMap(ctx))
    , computer(UIComputer(ctx))
    , diary(UIDiary(ctx))
{
    inventory.add_item(Item::PICKAXE);
    inventory.add_item(Item::SHOVEL);
    inventory.add_item(Item::CHISEL);

    ctx->play_sound(Sound::DIARY_SCRIBBLE);
    ctx->play_sound(Sound::DIARY_SLIDE);

    SDL_StartTextInput();
}

UI::~UI() {
    // SDL_DestroyWindow(window);
    SDL_Quit();

    SDL_StopTextInput();
}

void UI::update() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
	if(e.type == SDL_QUIT) {
	    events.push(UIEvent_EXIT{});
	}
	if(e.type == SDL_KEYDOWN) {
	    if(e.key.keysym.sym == SDLK_TAB) {
		current_story = current_story == Story::DIARY ? Story::COMPUTER : Story::DIARY;
		diary.set_revealed(current_story == Story::DIARY);
	    } else if(e.key.keysym.sym == SDLK_BACKSPACE) {
		if(current_story == Story::DIARY) {
		    diary.input.remove_character();
		} else {
		    computer.input.remove_character();
		}
	    } else if(e.key.keysym.sym == SDLK_RETURN) {
		string content;
		if(current_story == Story::DIARY) {
		    if(diary.input.get_content().empty()) {
			return;
		    }
		    content = diary.input.get_content();

		    diary.log.add_message("> " + content);
		    diary.input.clear();
		} else {
		    if(computer.input.get_content().empty()) {
			return;
		    }
		    content = computer.input.get_content();

		    computer.log.add_message("> " + content);
		    computer.input.clear();
		}
		events.push(UIEvent_SEND_COMMAND{current_story, content});

	    }
	} else if(e.type == SDL_TEXTINPUT) {
	    if(current_story == Story::DIARY) {
		diary.input.add_string(e.text.text);
	    } else {
		computer.input.add_string(e.text.text);
	    }
	}
    }
}

bool UI::poll(UIEvent *event) {
    if(events.empty()) {
	return false;
    } 

    *event = events.front();
    events.pop();

    return true;
}

void UI::write(Story story, string text) {
    if(story == Story::DIARY) {
	ctx->play_sound(Sound::DIARY_SCRIBBLE);
	diary.log.add_message(text);
    } else {
	computer.log.add_message(text);
    }
}

void UI::play_sound(string name) {
    ctx->play_sound(name);
}

void UI::set_map_image(string name) {
    map.set_texture(name);
}

void UI::render_background() {
    SDL_Rect viewport = ctx->viewport_from_layout(LAYOUT_BACKGROUND);

    SDL_RenderSetViewport(ctx->renderer, &viewport);
    SDL_RenderCopy(ctx->renderer, ctx->assets.get_texture(Texture::BACKGROUND), NULL, NULL);
}

void UI::render() {
    // Clear
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(ctx->renderer);

    // Do stuff
    render_background();

    computer.render();
    diary.render();
    map.render();
    inventory.render();

    // Present
    SDL_RenderPresent(ctx->renderer);

    // Delay to match the framerate
    int time_now = SDL_GetPerformanceCounter();
    double time_taken = (double) (time_now - time_since_last_render) / ((double) SDL_GetPerformanceFrequency());
    time_taken = time_taken < 0 ? 0 : time_taken; // Sometimes this is zero

    SDL_Delay(std::max(0.0, (1/fps - time_taken) * 1000));

    time_since_last_render = SDL_GetPerformanceCounter();
}
