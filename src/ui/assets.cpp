#include <SDL_ttf.h>
#include <iostream>

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "ui/assets.hpp"
#include "ui/ui.hpp"
#include "utils/file_access.hpp"

AssetManager::AssetManager(SDL_Renderer *renderer)
    : renderer(renderer)
    , accessor(FileAccessor("assets")) {}

AssetManager::~AssetManager() {
    unload_assets();
}

SDL_Texture *AssetManager::get_texture(string name) {
    if(textures.count(name)) {
	return textures[name];
    } else {
	SDL_Texture *texture;
	if((texture = IMG_LoadTexture(renderer, accessor.get_full_path("textures/" + name).c_str())) == NULL) {
	    std::cerr << "ERROR: Could not find texture " << accessor.get_full_path("textures/" + name).c_str() << std::endl;
	}
	textures[name] = texture;
	return texture;
    }
}

SDL_Texture *AssetManager::get_texture(Texture texture) {
    return get_texture(TEXTURE_TO_NAME.at(texture));
}

Mix_Chunk *AssetManager::get_sound(string name) {
    if(sounds.count(name)) {
	return sounds[name];
    } else {
	Mix_Chunk *sound;
	if((sound = Mix_LoadWAV(accessor.get_full_path("sounds/" + name).c_str())) == NULL) {
	    std::cerr << "ERROR: Could not find sound " << accessor.get_full_path("sounds/" + name).c_str() << std::endl;
	}
	sounds[name] = sound;
	return sound;
    }
}

Mix_Chunk *AssetManager::get_sound(Sound sound) {
    return get_sound(SOUND_TO_NAME.at(sound));
}

TTF_Font *AssetManager::get_font(string name, int size) {
    if(fonts.count({name, size})) {
	return fonts[{name, size}];
    } else {
	TTF_Font *font;
	if((font = TTF_OpenFont(accessor.get_full_path("fonts/" + name).c_str(), size)) == NULL) {
	    std::cerr << "ERROR: Could not find font " << accessor.get_full_path("fonts/" + name).c_str() << std::endl;
	}
	fonts[{name, size}] = font;
	return font;
    }
}

TTF_Font *AssetManager::get_font(Font font) {
    return get_font(FONT_TO_NAME.at(font), FONT_TO_SIZE.at(font));
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
