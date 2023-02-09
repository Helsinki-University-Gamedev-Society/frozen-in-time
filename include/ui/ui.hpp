#include "SDL.h"
#include "SDL_rect.h"

#include <algorithm>
#include <queue>

using std::queue;

#define WINDOW_TITLE "GAMING TIME!"
#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768


template <typename T>
class Animation {
protected:
    T current_state;
public:
    virtual void progress(double dt) = 0;
    virtual bool is_finished() = 0;
    T get_current_state() {return current_state;}
};

class EaseOutExpoAnimation: public Animation<SDL_Point> {
private:
    SDL_Point from;
    SDL_Point to;
    double total_time;
    double current_time = 0;
public:
    EaseOutExpoAnimation(SDL_Point from, SDL_Point to, double time);
    void progress(double dt);
    bool is_finished();
};

enum class UIEvent_Type {
    EXIT,
};

struct UIEvent {
public:
    UIEvent_Type type;
};

class UI {
private:
    double time_last;

    EaseOutExpoAnimation slide_anim;
public:
    UI();
    ~UI();

    void update();
    bool poll(UIEvent *event);
    void render();
private: // Private rendering functions
    void render_background();
private:
    queue<UIEvent> events;

    SDL_Window *window { nullptr };
    SDL_Renderer *renderer { nullptr };

};
