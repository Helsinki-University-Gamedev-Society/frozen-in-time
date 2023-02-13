#include <SDL_ttf.h>
#include <algorithm>
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
    , total_time(time)
    , current_state(from) {}

void EaseOutExpoAnimation::progress(double dt) {
    if(current_time > total_time) {
	return;
    }
    current_time += dt;

    double p_t = current_time / total_time;
    double p_d = p_t >= 0.75 ? 1 : 1 - pow(2, -10 * p_t);

    current_state = SDL_Point{(int) (p_d * to.x + (1 - p_d) * from.x),
			      (int) (p_d * to.y + (1 - p_d) * from.y)};
}

bool EaseOutExpoAnimation::is_finished() {
    return current_time >= total_time;
}

FadeInText::FadeInText(shared_ptr<GraphicsContext> ctx, string content, Font font, SDL_Color color, int layout_width, double time)
    : ctx(ctx)
    , content(content)
    , font(font)
    , color(color)
    , layout_width(layout_width)
    , total_time(time) {}

void FadeInText::progress(double dt) {
    if(current_time > total_time) {
	return;
    }
    current_time += dt;
}

SDL_Texture *FadeInText::get_current_texture() {
    int width = ctx->width_from_layout_width(layout_width);

    if(last_width != width) {
	SDL_DestroyTexture(current_texture);
	Text text = Text(ctx->renderer, content, ctx->assets.get_font(font), color, width);
	current_texture = text.get_texture();
    }

    last_width = width;

    int text_w, text_h;
    SDL_QueryTexture(current_texture, NULL, NULL, &text_w, &text_h);

    uint alpha = 255.0 * std::min(1.0, current_time / total_time);
    SDL_SetTextureAlphaMod(current_texture, alpha);

    return current_texture;
}

FlashingCursorAnimation::FlashingCursorAnimation(double time_vis, double time_invis)
    : time_vis(time_vis)
    , time_invis(time_invis) {}

void FlashingCursorAnimation::progress(double dt) {
    time_mod = fmod(time_mod + dt, time_vis + time_invis);
    visible = time_mod < time_vis;
}
