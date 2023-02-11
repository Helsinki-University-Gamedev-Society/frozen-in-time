#include <SDL_ttf.h>
#include <iostream>

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "ui/assets.hpp"
#include "ui/ui.hpp"

AssetManager::AssetManager(SDL_Renderer *renderer) {
    load_assets(renderer);
}

AssetManager::~AssetManager() {
    unload_assets();
}

void AssetManager::load_assets(SDL_Renderer *renderer) {
    std::cout << "Loading assets..." << std::endl;

    for(const auto& [name, path] : TEXTURE_TO_FILE) {
	SDL_Texture *texture;
	if((texture = IMG_LoadTexture(renderer,  ("assets/" + path).c_str())) == NULL) {
	    std::cout << "ERROR: Could not find texture " << path << std::endl;
	}
	textures[name] = texture;
    }

    for(const auto& [name, path] : SOUND_TO_FILE) {
	Mix_Chunk *sound;
	if((sound = Mix_LoadWAV(("assets/" + path).c_str())) == NULL) {
	    std::cout << "ERROR: Could not find sound " << path << std::endl;
	}
	sounds[name] = sound;
    } 

    for(const auto& [name, path] : FONT_TO_FILE) {
	TTF_Font *font;
	if((font = TTF_OpenFont(("assets/" + path).c_str(), FONT_SIZE)) == NULL) {
	    std::cout << "ERROR: Could not find sound " << path << std::endl;
	}
	fonts[name] = font;
    } 

    std::cout << "Assets loaded" << std::endl;
}

void AssetManager::unload_assets() {
    for(const auto &[name, texture] : textures) {
	SDL_DestroyTexture(texture);
    }

    for(const auto &[name, sound] : sounds) {
	Mix_FreeChunk(sound);
    }

    for(const auto &[name, font] : fonts) {
	TTF_CloseFont(font);
    }
}
