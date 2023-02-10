#ifndef _UI_UI_
#define _UI_UI_

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_rect.h>

#include <algorithm>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "ui/assets.hpp"
#include "ui/animations.hpp"
#include "ui/ui_elements.hpp"

using std::queue;
using std::shared_ptr;
using std::string;

#define WINDOW_TITLE "GAMING TIME!"
#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

enum class UIEvent_Type {
    EXIT,
    SWITCH_TIMELINE,
};

struct UIEvent {
public:
    UIEvent_Type type;
};

class UI {
private:
    double time_last;

    bool diary_on_screen = true;
    EaseOutExpoAnimation slide_anim;
public:
    UI();
    ~UI();

    void update();
    bool poll(UIEvent *event);
    void render();
private: // Private SDL2-related functions
    void update_animations();
    void render_background();
    void render_map();
    void play_sound(Sound sound);
private:
    queue<UIEvent> events;

    SDL_Window *window { nullptr };
    SDL_Renderer *renderer { nullptr };

    shared_ptr<AssetManager> assets;
private: // Child elements
    UIInventory inventory;
};

#endif // _UI_UI_
