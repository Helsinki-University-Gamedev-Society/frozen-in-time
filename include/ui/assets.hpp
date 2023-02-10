#ifndef _UI_ASSETS_
#define _UI_ASSETS_

#include <map>
#include <string>

#include <SDL_image.h>
#include <SDL_mixer.h>

using std::map;
using std::string;

enum class Item {
    CARROT = 0,
};

enum class Sound {
    DIARY_SLIDE = 0,
};

enum class Texture {
    BACKGROUND = 0,
    MAP,
    CARROT,
};

const map<Texture, string> TEXTURE_TO_FILE = {
    {Texture::BACKGROUND, "dark-wood-background.jpg"},
    {Texture::MAP,        "diary-background.jpg"},
    {Texture::CARROT,     "vili-carrot.png"},
};

const map<Sound, string> SOUND_TO_FILE = {
    {Sound::DIARY_SLIDE, "diary-sliding.wav"},
};

const map<Item, Texture> ITEM_TO_TEXTURE = {
    {Item::CARROT, Texture::CARROT}
};

class AssetManager {
public:
    AssetManager(SDL_Renderer *renderer);
    ~AssetManager();
public:
    map<Texture, SDL_Texture *> textures;
    map<Sound, Mix_Chunk *> sounds;
private:
    void load_assets(SDL_Renderer *renderer);
    void unload_assets();
};

#endif // _UI_ASSETS_
