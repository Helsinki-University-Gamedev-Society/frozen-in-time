#ifndef _TEXT_H_
#define _TEXT_H_

#include <string>

#include <SDL_ttf.h>
#include <utility>

using std::pair;
using std::string;

// In the future, this could be updated to use a font atlas
// The benefit over the current implementation would be that rendering a texture each time
// you want to enter a piece of text takes a long time
class Text {
public:
    Text(SDL_Renderer *renderer, string content, TTF_Font *font, SDL_Color color, int max_width);
    ~Text();

    SDL_Texture *get_texture();
    pair<int, int> get_size();
    string get_content();
private:
    int max_width;
    string content;
    SDL_Texture *texture { nullptr };
};

#endif // _TEXT_H_
