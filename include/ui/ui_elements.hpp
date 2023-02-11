#ifndef _UI_ELEMENTS_
#define _UI_ELEMENTS_

#include <memory>
#include <optional>
#include <vector>

#include <SDL_rect.h>
#include <SDL_render.h>

#include "ui/animations.hpp"
#include "ui/assets.hpp"
#include "ui/text.hpp"

using std::shared_ptr;
using std::vector;

class GraphicsContext {
public:
    GraphicsContext();
    void play_sound(Sound sound);
public:
    SDL_Window *window { nullptr };
    SDL_Renderer *renderer { nullptr };
    AssetManager assets;
};

shared_ptr<GraphicsContext> init_graphics();

class UIInventory {
public:
    UIInventory(shared_ptr<GraphicsContext> ctx, int items_hori);
    void render(SDL_Rect viewport);

    void add_item(Item item);
private:
    int items_hori;
    shared_ptr<GraphicsContext> ctx;
private:
    vector<Item> items;
};

class UIMap {
public:
    UIMap();
    void render(SDL_Rect viewport);
};

class UIMessageLog {
public:
    UIMessageLog(shared_ptr<GraphicsContext> ctx);
    void render(SDL_Rect viewport);

    void add_text(Text text);
private:
    Font font;

    vector<TextAppearAnimation> messages;
    shared_ptr<GraphicsContext> ctx;
};

class UIInputField {
public:
    UIInputField(shared_ptr<GraphicsContext> ctx, Font font, SDL_Color color, int default_width);
    void render(SDL_Rect viewport);

    void add_character(char c);
    void remove_character();
private:
    Font font;
    SDL_Color color;
    int default_width;

    string content;
    Text text;

    shared_ptr<GraphicsContext> ctx;
};

#endif // _UI_ELEMENTS_
