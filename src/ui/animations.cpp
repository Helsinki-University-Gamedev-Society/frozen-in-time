#include <cmath>

#include "ui/animations.hpp"

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
