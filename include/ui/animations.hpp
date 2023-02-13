#ifndef _UI_ANIMATIONS_
#define _UI_ANIMATIONS_

#include <SDL.h>
#include <SDL_render.h>

#include "ui/context.hpp"
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

class FadeInText: public Animation {
private:
    SDL_Texture *current_texture;
public:
    FadeInText(shared_ptr<GraphicsContext> ctx, string content, Font font, int layout_width, double appear_time, double fade_time);

    bool is_finished();
    SDL_Texture *get_current_texture();
    pair<int, int> get_size();
private:
    void progress(double dt);
private:
    string content;
    Font font;
    int layout_width;

    int last_width;
    double appear_time;
    double fade_time;
    double current_time = 0;

    shared_ptr<GraphicsContext> ctx;
};

class FlashingCursorAnimation: public Animation {
private:
    bool visible;
public:
    FlashingCursorAnimation(double time_vis, double time_invis);

    bool is_visible() {return visible;}
private:
    void progress(double dt);
private:
    double time_vis;
    double time_invis;

    double time_mod = 0;
};

#endif // _UI_ANIMATIONS_
