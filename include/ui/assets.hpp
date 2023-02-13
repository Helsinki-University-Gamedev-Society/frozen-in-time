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
    TITLE_SCREEN,
    MAP,
    DIARY,
    CARROT,
    PICKAXE,
    SHOVEL,
    CHISEL,
};

enum class Music {
    THEME_TUNE = 0,
};

enum class Font {
    PRESENT_PLAYER_SPEAKING = 0,
    PRESENT_PLAYER_THINKING,
    PRESENT_OTHER_CHARACTER,
    PRESENT_NARRATION,

    PAST_WRITING,
};

struct FontStyleSpec {
    string name;
    int size;
    SDL_Color color;
    string marker;
};

const map<Font, FontStyleSpec> FONT_TO_SPEC {
    {{Font::PRESENT_PLAYER_SPEAKING, {"pixelfjverdana.regular.ttf", 15, {0xA0, 0xDB, 0x85, 0xFF}, ""}},
     {Font::PRESENT_PLAYER_THINKING, {"pixelfjverdana.regular.ttf", 15, {0xA0, 0xDB, 0x85, 0xFF}, "*"}},
     {Font::PRESENT_OTHER_CHARACTER, {"pixelfjverdana.regular.ttf", 15, {0xBC, 0xBC, 0xBC, 0xFF}, ""}},
     {Font::PRESENT_NARRATION,       {"pixelfjverdana.regular.ttf", 15, {0xBC, 0xBC, 0xBC, 0xFF}, ""}},

     {Font::PAST_WRITING,            {"dpcomic.regular.ttf",        40, {0x44, 0x44, 0x44, 0xFF}, ""}}}
};

const map<Texture, string> TEXTURE_TO_NAME = {
    {Texture::BACKGROUND,   "background.png"},
    {Texture::TITLE_SCREEN, "background.png"},
    {Texture::MAP,          "parchment2.png"},
    {Texture::DIARY,        "diary.png"},

    {Texture::CARROT,       "vili-carrot.png"},
    {Texture::PICKAXE,      "item_pickaxe.png"},
    {Texture::SHOVEL,       "item_shovel.png"},
    {Texture::CHISEL,       "item_chisel.png"},
};

const map<Sound, string> SOUND_TO_NAME = {
    {Sound::DIARY_SLIDE,    "diary-sliding.wav"},
    {Sound::DIARY_SCRIBBLE, "diary-scribble.wav"},
};

const map<Music, string> MUSIC_TO_NAME = {
    {Music::THEME_TUNE, "paulstretched-uncertainty.ogg"}
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

    Mix_Music *get_music(string name);
    Mix_Music *get_music(Music music);
private:
    void unload_assets();
private:
    map<string, SDL_Texture *> textures;
    map<string, Mix_Chunk *> sounds;
    map<pair<string, int>, TTF_Font *> fonts;
    map<string, Mix_Music *> musics;

    SDL_Renderer *renderer;
    FileAccessor accessor;
};

#endif // _UI_ASSETS_
