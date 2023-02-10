#ifndef _UI_ELEMENTS_
#define _UI_ELEMENTS_

#include <memory>
#include <vector>

#include <SDL_rect.h>
#include <SDL_render.h>

#include "ui/assets.hpp"

using std::shared_ptr;
using std::vector;

class UIInventory {
public:
    UIInventory(shared_ptr<AssetManager>, int items_hori);
    void render(SDL_Renderer *renderer, SDL_Rect viewport);

    void add_item(Item item);
private:
    int items_hori;
    shared_ptr<AssetManager> assets;
private:
    vector<Item> items;
};

class UIMap {
public:
    UIMap();
    void render(SDL_Renderer renderer, SDL_Rect viewport);
};

#endif // _UI_ELEMENTS_
