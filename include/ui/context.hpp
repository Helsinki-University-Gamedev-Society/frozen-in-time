#include <memory>

#include <SDL_rect.h>

#include "ui/assets.hpp"

using std::shared_ptr;

class GraphicsContext {
public:
    GraphicsContext();

    void play_sound(Sound sound);
    SDL_Rect viewport_from_layout(SDL_Rect layout);
    int width_from_layout_width(int layout_width);
    SDL_Rect game_viewport();
public:
    SDL_Window *window { nullptr };
    SDL_Renderer *renderer { nullptr };
    AssetManager assets;
};

shared_ptr<GraphicsContext> init_graphics();
