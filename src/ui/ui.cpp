#include <SDL_keycode.h>

#include <SDL_rect.h>
#include <iostream>
#include <memory>

#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_timer.h>

#include "ui/animations.hpp"
#include "ui/assets.hpp"
#include "ui/ui.hpp"
#include "ui/ui_elements.hpp"

GraphicsContext::GraphicsContext()
    : window(SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0))
    , renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE))
    , assets(AssetManager(renderer))
{}

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

UI::UI(shared_ptr<GraphicsContext> ctx)
    : ctx(ctx)
    , slide_anim(EaseOutExpoAnimation(SDL_Point{7 * WINDOW_WIDTH / 14, WINDOW_HEIGHT / 10}, SDL_Point{9 * WINDOW_WIDTH / 14, WINDOW_HEIGHT / 10}, 1.0))
    , inventory(UIInventory(ctx, 8))
    , diary_log(UIMessageLog(ctx))
{
    inventory.add_item(Item::CARROT);
    inventory.add_item(Item::CARROT);
    inventory.add_item(Item::CARROT);
    inventory.add_item(Item::CARROT);
    inventory.add_item(Item::CARROT);

    ctx->play_sound(Sound::DIARY_SCRIBBLE);
    ctx->play_sound(Sound::DIARY_SLIDE);
}

UI::~UI() {
    // SDL_DestroyWindow(window);
    SDL_Quit();
}

void UI::update() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
	if(e.type == SDL_QUIT) {
	    events.push(UIEvent{UIEvent_Type::EXIT});
	}
	if(e.type == SDL_KEYDOWN) {
	    if(e.key.keysym.sym == SDLK_TAB) {
		if(slide_anim.is_finished()) {
		    if(diary_on_screen) {
			slide_anim = EaseOutExpoAnimation(SDL_Point{9 * WINDOW_WIDTH / 14, WINDOW_HEIGHT / 10}, SDL_Point{7 * WINDOW_WIDTH / 14, WINDOW_HEIGHT / 10}, 1.0);
		    } else {
			slide_anim = EaseOutExpoAnimation(SDL_Point{7 * WINDOW_WIDTH / 14, WINDOW_HEIGHT / 10}, SDL_Point{9 * WINDOW_WIDTH / 14, WINDOW_HEIGHT / 10}, 1.0);
		    }

		    slide_anim.start();
		    ctx->play_sound(Sound::DIARY_SLIDE);

		    diary_on_screen = not diary_on_screen;
		    events.push(UIEvent{UIEvent_Type::SWITCH_TIMELINE});
		}
	    } else if(e.key.keysym.sym == SDLK_RETURN) {
		ctx->play_sound(Sound::DIARY_SCRIBBLE);
		diary_log.add_text(Text(ctx->renderer,
					"This is some test text! Hahahahahah! I am having a great time! I hope you are enjoying this here text adventure!!!!!",
					ctx->assets.fonts[Font::DIARY_FONT],
					SDL_Color{0x00, 0x00, 0x00, 0xFF},
					500));
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
    SDL_Rect full_viewport {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    SDL_RenderSetViewport(ctx->renderer, &full_viewport);
    SDL_RenderCopy(ctx->renderer, ctx->assets.textures[Texture::BACKGROUND], NULL, NULL);
}

void UI::render_map() {
    SDL_Point left_corner = slide_anim.get_current_state();
    SDL_Rect map_viewport {left_corner.x, left_corner.y, 4 * WINDOW_WIDTH / 14, 4 * WINDOW_HEIGHT / 10};

    SDL_RenderSetViewport(ctx->renderer, &map_viewport);
    SDL_RenderCopy(ctx->renderer, ctx->assets.textures[Texture::MAP], NULL, NULL);

    // SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, SDL_ALPHA_OPAQUE);
    // SDL_Rect rect{0, 50, 100, 100};
    // SDL_RenderFillRect(renderer, &rect);
}

void UI::update_animations() {
    if(not slide_anim.has_started()) {
	slide_anim.start();
    }
    slide_anim.update();
}

void UI::render() {
    // Clear
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(ctx->renderer);

    // Do stuff
    update_animations();
    render_background();
    render_map();

    diary_log.render(SDL_Rect{0, 1 * WINDOW_HEIGHT / 10, 7 * WINDOW_WIDTH / 14, 8 * WINDOW_HEIGHT / 10});

    inventory.render(SDL_Rect{9 * WINDOW_WIDTH / 14, 6 * WINDOW_HEIGHT / 10, 4 * WINDOW_WIDTH / 14, 4 * WINDOW_HEIGHT / 10});

    // Present
    SDL_RenderPresent(ctx->renderer);
}
