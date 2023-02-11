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

#define MESSAGE_SPACING 20

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
    bool diary_on_screen = true;
    EaseOutExpoAnimation slide_anim;
public:
    UI(shared_ptr<GraphicsContext> ctx);
    ~UI();

    void update();
    bool poll(UIEvent *event);
    void render();
private: // Private SDL2-related functions
    void update_animations();
    void render_background();
    void render_map();
private:
    queue<UIEvent> events;
    shared_ptr<GraphicsContext> ctx;
private: // Child elements
    UIInventory inventory;
    UIMessageLog diary_log;
};

#endif // _UI_UI_
