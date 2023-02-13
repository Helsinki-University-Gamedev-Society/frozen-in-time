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
#include <variant>
#include <vector>

#include "ui/assets.hpp"
#include "ui/animations.hpp"
#include "ui/ui_elements.hpp"

using std::queue;
using std::shared_ptr;
using std::string;

#define WINDOW_TITLE "GAMING TIME!"
// #define WINDOW_WIDTH 1366
// #define WINDOW_HEIGHT 768

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

enum class Story {
    COMPUTER,
    DIARY
};

enum class UIEvent_Type {
    EXIT,
    SWITCH_TIMELINE,
};

struct UIEvent_EXIT {};
struct UIEvent_SEND_COMMAND {
    Story story;
    string command;
};

using UIEvent = std::variant<UIEvent_EXIT, UIEvent_SEND_COMMAND>;

template <typename T>
bool UIEvent_of_type(UIEvent &event) {
    return std::holds_alternative<T>(event);
}

class UI {
private:
    Story current_story;
    double fps = 120;
public:
    UI(shared_ptr<GraphicsContext> ctx);
    ~UI();

    void update();
    bool poll(UIEvent *event);

    void write(Story story, string text);
    void play_sound(string name);
    void set_map_image(string name);

    void render();
private:
    void render_background();
private: // Child elements
    UIInventory inventory;
    UIMap map;
    UIComputer computer;
    UIDiary diary;
private:
    double time_since_last_render = 0;
    queue<UIEvent> events;
    shared_ptr<GraphicsContext> ctx;
};

#endif // _UI_UI_
