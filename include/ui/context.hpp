#ifndef _UI_CONTEXT_
#define _UI_CONTEXT_

#include <memory>

#include <SDL_rect.h>

#include "ui/assets.hpp"

using std::shared_ptr;

class GraphicsContext {
public:
    GraphicsContext();

    void play_sound(string sound);
    void play_sound(Sound sound);

    void play_music(string music);
    void play_music(Music music);

    void resume_music();
    void pause_music();
    void stop_music();

    void set_music_volume(double volume);
    void adjust_music_volume(double d_volume);

    SDL_Rect viewport_from_layout(SDL_Rect layout);
    int width_from_layout_width(int layout_width);
    SDL_Rect game_viewport();
public:
    SDL_Window *window { nullptr };
    SDL_Renderer *renderer { nullptr };
    AssetManager assets;
private:
    double music_volume;
};

shared_ptr<GraphicsContext> init_graphics();

#endif // _UI_CONTEXT_
