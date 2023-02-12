#include <cmath>
#include <iostream>

#include <SDL_rect.h>
#include <SDL_render.h>

#include "ui/animations.hpp"

void Animation::start() {
    started = true;
}

void Animation::update() {
    double time_now = SDL_GetPerformanceCounter();
    double delta_time = (time_now - time_last_updated) / (double) SDL_GetPerformanceFrequency();

    if(started) {
	progress(delta_time);
    }

    time_last_updated = time_now;
}

bool Animation::has_started() {
    return started;
}

EaseOutExpoAnimation::EaseOutExpoAnimation(SDL_Point from, SDL_Point to, double time)
    : from(from)
    , to(to)
    , total_time(time) {}

void EaseOutExpoAnimation::progress(double dt) {
    current_time += dt;
    current_time = current_time > total_time ? total_time : current_time;

    double p_t = current_time / total_time;
    double p_d = p_t >= 0.75 ? 1 : 1 - pow(2, -10 * p_t);

    current_state = SDL_Point{(int) (p_d * to.x + (1 - p_d) * from.x),
			      (int) (p_d * to.y + (1 - p_d) * from.y)};
}

bool EaseOutExpoAnimation::is_finished() {
    return current_time >= total_time;
}

FadeInAnimation::FadeInAnimation(SDL_Texture *texture, double time)
    : texture(texture)
    , total_time(time) {}

void FadeInAnimation::progress(double dt) {
    current_time += dt;
    current_time = current_time > total_time  ? total_time : current_time;
}

void FadeInAnimation::render(SDL_Renderer *renderer, SDL_Rect target) {
    auto [w, h] = get_size();

    if(current_time >= total_time) {
	SDL_RenderCopy(renderer, texture, NULL, &target);
    }
}

pair<int, int> FadeInAnimation::get_size() {
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    return {width, height};

}

FlashingCursorAnimation::FlashingCursorAnimation(double time_vis, double time_invis)
    : time_vis(time_vis)
    , time_invis(time_invis) {}

void FlashingCursorAnimation::progress(double dt) {
    time_mod = fmod(time_mod + dt, time_vis + time_invis);
    visible = time_mod < time_vis;
}
