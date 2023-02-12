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
    , renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE))
    , assets(AssetManager(renderer)) {}

void GraphicsContext::play_sound(Sound sound) {
    Mix_PlayChannel(-1, assets.sounds[sound], 0);
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
		diary_on_screen = not diary_on_screen;
		diary.set_revealed(diary_on_screen);
	    } else if(e.key.keysym.sym == SDLK_BACKSPACE) {
		if(diary_on_screen) {
		    diary.input.remove_character();
		} else {
		    computer.input.remove_character();
		}
	    } else if(e.key.keysym.sym == SDLK_RETURN) {
		string content;
		if(diary_on_screen) {
		    if(diary.input.get_content().empty()) {
			return;
		    }
		    content = diary.input.get_content();

		    diary.log.add_message("> " + content);
		    diary.input.clear();

		    ctx->play_sound(Sound::DIARY_SCRIBBLE);
		} else {
		    if(computer.input.get_content().empty()) {
			return;
		    }
		    content = computer.input.get_content();

		    computer.log.add_message("> " + content);
		    computer.input.clear();
		    // ctx->play_sound(Sound::DIARY_SCRIBBLE);
		}
		events.push(UIEvent_SEND_COMMAND{diary_on_screen, content});

	    }
	} else if(e.type == SDL_TEXTINPUT) {
	    if(diary_on_screen) {
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

void UI::render_background() {
    // SDL_Rect full_viewport {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_Rect viewport = ctx->viewport_from_layout(LAYOUT_BACKGROUND);

    SDL_RenderSetViewport(ctx->renderer, &viewport);
    SDL_RenderCopy(ctx->renderer, ctx->assets.textures[Texture::BACKGROUND], NULL, NULL);
}

void UI::render_map() {
    SDL_Rect viewport = ctx->viewport_from_layout(LAYOUT_MAP);

    SDL_RenderSetViewport(ctx->renderer, &viewport);
    SDL_RenderCopy(ctx->renderer, ctx->assets.textures[Texture::MAP], NULL, NULL);
}

void UI::render() {
    // Clear
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(ctx->renderer);

    // Do stuff
    render_background();
    render_map();

    computer.render();
    diary.render();
    inventory.render();

    // Present
    SDL_RenderPresent(ctx->renderer);
}
