#include <cmath>

#include <iostream>

#include "SDL_events.h"
#include "SDL_timer.h"
#include "ui/ui.hpp"
#include "SDL_render.h"

EaseOutExpoAnimation::EaseOutExpoAnimation(SDL_Point from, SDL_Point to, double time):
    from(from),
    to(to),
    total_time(time) {}

void EaseOutExpoAnimation::progress(double dt) {
    current_time += dt;
    current_time = current_time > total_time ? total_time : current_time;

    double p_t = current_time / total_time;
    double p_d = p_t == 1 ? 1 : 1 - pow(2, -10 * p_t);

    current_state = SDL_Point{(int) (p_d * to.x + (1 - p_d) * from.x),
			      (int) (p_d * to.y + (1 - p_d) * from.y)};
}

bool EaseOutExpoAnimation::is_finished() {
    return current_time >= total_time;
}

UI::UI()
    : slide_anim(EaseOutExpoAnimation(SDL_Point{7 * WINDOW_WIDTH / 14, WINDOW_HEIGHT / 10}, SDL_Point{9 * WINDOW_WIDTH / 14, WINDOW_HEIGHT / 10}, 1.0)) {
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
			      SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    time_last = SDL_GetPerformanceCounter();
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
    
}

void UI::render() {
    double time_now = SDL_GetPerformanceCounter();
    double delta_time = (time_now - time_last) / (double) SDL_GetPerformanceFrequency();
    time_last = time_now;

    slide_anim.progress(delta_time);
    SDL_Point left_corner = slide_anim.get_current_state();

    SDL_Rect map_viewport {left_corner.x, left_corner.y, 4 * WINDOW_WIDTH / 14, 4 * WINDOW_HEIGHT / 10};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_RenderSetViewport(renderer, &map_viewport);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_Rect rect{0, 50, 100, 100};
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}
