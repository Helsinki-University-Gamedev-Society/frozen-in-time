#include "ui/assets.hpp"
#include "ui/ui.hpp"
#include "ui/context.hpp"
#include <SDL_mixer.h>

GraphicsContext::GraphicsContext()
    : window(SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0))
    , renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))
    , assets(AssetManager(renderer)) {}

void GraphicsContext::play_sound(string sound) {
    Mix_PlayChannel(-1, assets.get_sound(sound), 0);
}

void GraphicsContext::play_sound(Sound sound) {
    Mix_PlayChannel(-1, assets.get_sound(sound), 0);
}

void GraphicsContext::play_music(string music) {
    Mix_PlayMusic(assets.get_music(music), -1);
}

void GraphicsContext::play_music(Music music) {
    play_music(MUSIC_TO_NAME.at(music));
}

void GraphicsContext::resume_music() {
    Mix_ResumeMusic();
}

void GraphicsContext::pause_music() {
    Mix_PauseMusic();
}

void GraphicsContext::stop_music() {
    Mix_HaltMusic();
}

void GraphicsContext::set_music_volume(double volume) {
    music_volume = std::max(0.0, std::min(volume, 1.0));
    Mix_VolumeMusic(music_volume * MIX_MAX_VOLUME);
}

void GraphicsContext::adjust_music_volume(double d_volume) {
    music_volume = std::max(0.0, std::min(music_volume + d_volume, 1.0));
    Mix_VolumeMusic(music_volume * MIX_MAX_VOLUME);
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

SDL_Rect GraphicsContext::game_viewport() {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    int game_width = std::min(width, 16 * height / 9);
    int game_height = game_width * 9 / 16;

    int top_left_x = (width - game_width) / 2;
    int top_left_y = (height - game_height) / 2;

    return SDL_Rect{top_left_x, top_left_y, game_width, game_height};
}

SDL_Rect GraphicsContext::viewport_from_layout(SDL_Rect layout) {
    SDL_Rect game_rect = game_viewport();
	
    double scale = ((double) game_rect.w) / ((double) LAYOUT_BACKGROUND.w);

    return SDL_Rect{
	(int) (game_rect.x + layout.x * scale),
	(int) (game_rect.y + layout.y * scale),
	(int) (layout.w * scale),
	(int) (layout.h * scale),
    };
}

int GraphicsContext::width_from_layout_width(int layout_width) {
    SDL_Rect game_rect = game_viewport();

    double scale = ((double) game_rect.w) / ((double) LAYOUT_BACKGROUND.w);

    return (int) (layout_width * scale);
}

