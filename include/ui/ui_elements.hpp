#ifndef _UI_ELEMENTS_
#define _UI_ELEMENTS_

#include <deque>
#include <memory>
#include <optional>
#include <vector>

#include <SDL_rect.h>
#include <SDL_render.h>

#include "ui/animations.hpp"
#include "ui/assets.hpp"
#include "ui/layout.hpp"
#include "ui/text.hpp"

using std::deque;
using std::shared_ptr;
using std::vector;

class UIInventory {
public:
    UIInventory(shared_ptr<GraphicsContext> ctx);
    void render();

    void add_item(string name);
    void add_item(Item item);

    void remove_item(string name);
    void remove_item(Item item);
private:
    shared_ptr<GraphicsContext> ctx;
private:
    vector<string> items;
};

class UIMap {
public:
    UIMap(shared_ptr<GraphicsContext> ctx);
    void render();

    void set_texture(string name);
private:
    string texture_name;

    shared_ptr<GraphicsContext> ctx;
};

class UIMessageLog {
public:
    UIMessageLog(shared_ptr<GraphicsContext> ctx, pair<int, int> dims);
    void render(SDL_Point top_left);

    void add_message(string message, Font font, double appear_time);
private:
    Font font;
    SDL_Color color;
    pair<int, int> dims;

    deque<FadeInText> messages;
    shared_ptr<GraphicsContext> ctx;
};

class UIInputField {
public:
    UIInputField(shared_ptr<GraphicsContext> ctx, Font font, pair<int, int> dims);
    void render(SDL_Point top_left);

    string get_content();
    void add_string(string s);
    void remove_character();
    void clear();
private:
    Font font;
    pair<int, int> dims;

    string content;
    Text text;
    FlashingCursorAnimation cursor_visible;

    shared_ptr<GraphicsContext> ctx;
};

class UIDiary {
public:
    UIDiary(shared_ptr<GraphicsContext> ctx);
    void render();

    void set_revealed(bool reveal);
public:
    UIMessageLog log;
    UIInputField input;
private:
    bool revealed;

    shared_ptr<GraphicsContext> ctx;
    EaseOutExpoAnimation position;
};

class UIComputer {
public:
    UIComputer(shared_ptr<GraphicsContext> ctx);
    void render();
public:
    UIMessageLog log;
    UIInputField input;
private:
    shared_ptr<GraphicsContext> ctx;
};

class UITitleScreen {
public:
    UITitleScreen(shared_ptr<GraphicsContext> ctx);
    void render();

    void set_texture(string name);
private:
    string texture_name;

    shared_ptr<GraphicsContext> ctx;
};

#endif // _UI_ELEMENTS_
