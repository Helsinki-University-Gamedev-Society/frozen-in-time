#include <SDL_ttf.h>
#include <iostream>

#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_surface.h>

#include "ui/text.hpp"

Text::Text(SDL_Renderer *renderer, string content, TTF_Font *font, SDL_Color color, int max_width) {
    content = content;
    SDL_Surface *text_surface = TTF_RenderText_Blended_Wrapped(font, content.c_str(), color, max_width);
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    int width, height;

    SDL_FreeSurface(text_surface);
}

Text::~Text() {
    // SDL_DestroyTexture(texture);
}

SDL_Texture *Text::get_texture() {
    return texture;
}

pair<int, int> Text::get_size() {
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    return {width, height};
}

string Text::get_content() {
    return content;
}
