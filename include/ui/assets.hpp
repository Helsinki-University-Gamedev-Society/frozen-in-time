#ifndef _UI_ASSETS_
#define _UI_ASSETS_

#include <map>
#include <string>
#include <utility>

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_render.h>
#include <SDL_ttf.h>

#include "utils/file_access.hpp"

using std::map;
using std::pair;
using std::string;

enum class Item {
    CARROT = 0,
    PICKAXE,
    SHOVEL,
    CHISEL,
};

enum class Sound {
    DIARY_SLIDE = 0,
    DIARY_SCRIBBLE,
};

enum class Texture {
    BACKGROUND = 0,
    MAP,
    DIARY,
    CARROT,
    PICKAXE,
    SHOVEL,
    CHISEL,
};

enum class Font {
    COMPUTER_FONT = 0,
    DIARY_FONT = 1,
};

const map<Texture, string> TEXTURE_TO_NAME = {
    // {Texture::BACKGROUND, "dark-wood-background.jpg"},
    {Texture::BACKGROUND, "background.png"},
    // {Texture::MAP,        "diary-background.jpg"},
    {Texture::MAP,        "parchment2.png"},
    {Texture::DIARY,      "diary.png"},
    {Texture::CARROT,     "vili-carrot.png"},

    {Texture::PICKAXE,    "item_pickaxe.png"},
    {Texture::SHOVEL,     "item_shovel.png"},
    {Texture::CHISEL,     "item_chisel.png"},
};

const map<Sound, string> SOUND_TO_NAME = {
    {Sound::DIARY_SLIDE, "diary-sliding.wav"},
    {Sound::DIARY_SCRIBBLE, "diary-scribble.wav"},
};

const map<Font, string> FONT_TO_NAME = {
    {Font::COMPUTER_FONT, "pixelfjverdana.regular.ttf"},
    {Font::DIARY_FONT, "dpcomic.regular.ttf"},
};

const map<Font, int> FONT_TO_SIZE = {
    {Font::COMPUTER_FONT, 15},
    {Font::DIARY_FONT, 40},
};

const map<Item, Texture> ITEM_TO_TEXTURE = {
    {Item::CARROT,  Texture::CARROT},
    {Item::PICKAXE, Texture::PICKAXE},
    {Item::SHOVEL,  Texture::SHOVEL},
    {Item::CHISEL,  Texture::CHISEL},
};

class AssetManager {
public:
    AssetManager(SDL_Renderer *renderer);
    ~AssetManager();

    SDL_Texture *get_texture(string name);
    SDL_Texture *get_texture(Texture texture);

    Mix_Chunk *get_sound(string name);
    Mix_Chunk *get_sound(Sound sound);

    TTF_Font *get_font(string name, int size);
    TTF_Font *get_font(Font font);
private:
    void unload_assets();
private:
    map<string, SDL_Texture *> textures;
    map<string, Mix_Chunk *> sounds;
    map<pair<string, int>, TTF_Font *> fonts;

    SDL_Renderer *renderer;
    FileAccessor accessor;
};

#endif // _UI_ASSETS_
