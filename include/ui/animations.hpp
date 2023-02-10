#ifndef _UI_ANIMATIONS_
#define _UI_ANIMATIONS_

#include <SDL.h>

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

 #endif // _UI_ANIMATIONS_
