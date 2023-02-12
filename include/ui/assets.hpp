#ifndef _UI_ASSETS_
#define _UI_ASSETS_

#include <map>
#include <string>

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using std::map;
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

const map<Texture, string> TEXTURE_TO_FILE = {
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

const map<Sound, string> SOUND_TO_FILE = {
    {Sound::DIARY_SLIDE, "diary-sliding.wav"},
    {Sound::DIARY_SCRIBBLE, "diary-scribble.wav"},
};

const map<Font, string> FONT_TO_FILE = {
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
public:
    map<Texture, SDL_Texture *> textures;
    map<Sound, Mix_Chunk *> sounds;
    map<Font, TTF_Font *> fonts;
private:
    void load_assets(SDL_Renderer *renderer);
    void unload_assets();
};

#endif // _UI_ASSETS_
