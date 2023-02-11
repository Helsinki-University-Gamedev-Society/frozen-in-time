#ifndef _UI_ANIMATIONS_
#define _UI_ANIMATIONS_

#include <SDL.h>
#include <SDL_render.h>

#include "ui/text.hpp"

class Animation {
public:
    void start();
    void update();
    bool has_started();
private:
    virtual void progress(double dt) = 0;
private:
    bool started = false;
    double time_last_updated = SDL_GetPerformanceCounter();
};

class EaseOutExpoAnimation: public Animation {
private:
    SDL_Point current_state;
public:
    EaseOutExpoAnimation(SDL_Point from, SDL_Point to, double time);

    bool is_finished();
    SDL_Point get_current_state() {return current_state;}
private:
    void progress(double dt);
private:
    SDL_Point from;
    SDL_Point to;

    double total_time;
    double current_time = 0;
};

class TextAppearAnimation: public Animation {
public:
    TextAppearAnimation(Text text, double time);

    bool is_finished();
    void render(SDL_Renderer *renderer, SDL_Point location);
    pair<int, int> get_size();
private:
    void progress(double dt);
private:
    Text text;

    double total_time;
    double current_time = 0;
};

 #endif // _UI_ANIMATIONS_
