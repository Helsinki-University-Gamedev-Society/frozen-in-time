#include <SDL_keycode.h>

#include <SDL_rect.h>
#include <iostream>
#include <memory>

#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_timer.h>

#include "ui/assets.hpp"
#include "ui/ui.hpp"
#include "ui/ui_elements.hpp"

UI::UI()
    : window(SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0))
    , renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE))
    , assets(std::make_shared<AssetManager>(renderer))
    , slide_anim(EaseOutExpoAnimation(SDL_Point{7 * WINDOW_WIDTH / 14, WINDOW_HEIGHT / 10}, SDL_Point{9 * WINDOW_WIDTH / 14, WINDOW_HEIGHT / 10}, 1.0))
    , inventory(UIInventory(assets, 3))
{
    inventory.add_item(Item::CARROT);
    inventory.add_item(Item::CARROT);
    inventory.add_item(Item::CARROT);
    inventory.add_item(Item::CARROT);
    inventory.add_item(Item::CARROT);

    time_last = SDL_GetPerformanceCounter();

    play_sound(Sound::DIARY_SLIDE);
}

UI::~UI() {
    SDL_DestroyWindow(window);
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
		if(diary_on_screen) {
		    slide_anim = EaseOutExpoAnimation(SDL_Point{9 * WINDOW_WIDTH / 14, WINDOW_HEIGHT / 10}, SDL_Point{7 * WINDOW_WIDTH / 14, WINDOW_HEIGHT / 10}, 1.0);
		} else {
		    slide_anim = EaseOutExpoAnimation(SDL_Point{7 * WINDOW_WIDTH / 14, WINDOW_HEIGHT / 10}, SDL_Point{9 * WINDOW_WIDTH / 14, WINDOW_HEIGHT / 10}, 1.0);
		}
		play_sound(Sound::DIARY_SLIDE);

		diary_on_screen = not diary_on_screen;
		events.push(UIEvent{UIEvent_Type::SWITCH_TIMELINE});
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

    SDL_RenderSetViewport(renderer, &full_viewport);
    SDL_RenderCopy(renderer, assets->textures[Texture::BACKGROUND], NULL, NULL);
}

void UI::render_map() {
    SDL_Point left_corner = slide_anim.get_current_state();
    SDL_Rect map_viewport {left_corner.x, left_corner.y, 4 * WINDOW_WIDTH / 14, 4 * WINDOW_HEIGHT / 10};

    SDL_RenderSetViewport(renderer, &map_viewport);
    SDL_RenderCopy(renderer, assets->textures[Texture::MAP], NULL, NULL);

    // SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, SDL_ALPHA_OPAQUE);
    // SDL_Rect rect{0, 50, 100, 100};
    // SDL_RenderFillRect(renderer, &rect);
}

void UI::update_animations() {
    double time_now = SDL_GetPerformanceCounter();
    double delta_time = (time_now - time_last) / (double) SDL_GetPerformanceFrequency();
    time_last = time_now;

    slide_anim.progress(delta_time);
}

void UI::play_sound(Sound sound) {
    Mix_PlayChannel(-1, assets->sounds[sound], 0);
}

void UI::render() {
    // Clear
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Do stuff
    update_animations();
    render_background();
    render_map();

    inventory.render(renderer,
		     SDL_Rect{9 * WINDOW_WIDTH / 14, 6 * WINDOW_HEIGHT / 10, 4 * WINDOW_WIDTH / 14, 4 * WINDOW_HEIGHT / 10});

    // Present
    SDL_RenderPresent(renderer);
}
