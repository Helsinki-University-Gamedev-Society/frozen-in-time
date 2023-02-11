#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>

#include "ui/animations.hpp"
#include "ui/ui_elements.hpp"
#include "ui/assets.hpp"
#include "ui/ui.hpp"

UIInventory::UIInventory(shared_ptr<GraphicsContext> ctx, int items_hori):
    ctx(ctx), items_hori(items_hori) {}

void UIInventory::add_item(Item item) {
    items.push_back(item);
}

void UIInventory::render(SDL_Rect viewport) {
    SDL_RenderSetViewport(ctx->renderer, &viewport);

    int item_size = viewport.w / items_hori;

    int row = 0;
    int col = 0;

    SDL_Rect target_rect;
    for(const Item& item : items) {
	target_rect = {col * item_size, row * item_size,
		       item_size, item_size};

	SDL_RenderCopy(ctx->renderer, ctx->assets.textures[ITEM_TO_TEXTURE.at(item)], NULL, &target_rect);

	++col;
	if(col > items_hori) {
	    col = 0;
	    ++row;
	}
    }
}

UIMessageLog::UIMessageLog(shared_ptr<GraphicsContext> ctx): ctx(ctx) {}

void UIMessageLog::render(SDL_Rect viewport) {
    SDL_RenderSetViewport(ctx->renderer, &viewport);

    SDL_RenderCopy(ctx->renderer, ctx->assets.textures[Texture::MAP], NULL, NULL);

    int bottom_right_height = viewport.h;
    for(TextAppearAnimation message : messages) {
	message.update();
	auto [width, height] = message.get_size();

	message.render(ctx->renderer, SDL_Point{10, bottom_right_height - height});

	bottom_right_height -= height;
	bottom_right_height -= MESSAGE_SPACING;
    }
}

void UIMessageLog::add_text(Text text) {
    auto animation = TextAppearAnimation(text, 1.0);
    animation.start();


    messages.push_back(animation);
}

UIInputField::UIInputField(shared_ptr<GraphicsContext> ctx, Font font, SDL_Color color, int default_width)
    : ctx(ctx)
    , font(font)
    , color(color)
    , content("bananas")
    , text(Text(ctx->renderer, "", ctx->assets.fonts[font], color, default_width))
    , default_width(default_width) {

}

void UIInputField::render(SDL_Rect viewport) {
    if(content != text.get_content()) {
	text = Text(ctx->renderer, content, ctx->assets.fonts[font], color, default_width);
    }

    auto [text_w, text_h] = text.get_size();
    double text_aspect_ratio = ((double) text_w) / ((double) text_h);

    // We scale the text to fill up the viewport 
    double new_text_height = ((double) viewport.w) / text_aspect_ratio;

    SDL_Rect text_target = SDL_Rect {0, 0, viewport.w, (int) new_text_height};

    SDL_RenderSetViewport(ctx->renderer, &viewport);
    SDL_RenderCopy(ctx->renderer, text.get_texture(), NULL, &text_target);
}

void UIInputField::add_character(char c) {
    content.push_back(c);
}

void UIInputField::remove_character() {
    content.pop_back();
}
