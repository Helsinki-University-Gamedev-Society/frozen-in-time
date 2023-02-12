#include <iostream>

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

void UIInventory::render() {
    SDL_Rect viewport = ctx->viewport_from_layout(LAYOUT_INVENTORY_CONTENTS);
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

UIMessageLog::UIMessageLog(shared_ptr<GraphicsContext> ctx, pair<int, int> dims)
    : ctx(ctx)
    , dims(dims)
{}

void UIMessageLog::render(SDL_Point top_left) {
    SDL_Rect viewport = ctx->viewport_from_layout(SDL_Rect{
	    top_left.x, top_left.y,
	    dims.first, dims.second,
	});
    SDL_RenderSetViewport(ctx->renderer, &viewport);

    double scale = ((double) viewport.w) / ((double) dims.second);

    int bottom_right_height = viewport.h;
    for(FadeInAnimation message : messages) {
	message.update();
	auto [width, height] = message.get_size();

	int scaled_width = (int) (width * scale);
	int scaled_height = (int) (height * scale);

	message.render(ctx->renderer, SDL_Rect{0, bottom_right_height - height, scaled_width, scaled_height});

	bottom_right_height -= scaled_height;
	bottom_right_height -= MESSAGE_SPACING;

	if(bottom_right_height < 0) {
	    break;
	}
    }
}

void UIMessageLog::add_message(SDL_Texture *texture) {
    auto animation = FadeInAnimation(texture, 1.0);
    animation.start();

    messages.push_back(animation);
}

UIInputField::UIInputField(shared_ptr<GraphicsContext> ctx, Font font, SDL_Color color, pair<int, int> dims)
    : ctx(ctx)
    , font(font)
    , color(color)
    , content("bananas")
    , text(Text(ctx->renderer, "", ctx->assets.fonts[font], color, dims.first))
    , dims(dims)
    , cursor_visible(FlashingCursorAnimation(0.5, 0.5)) {
    cursor_visible.start();
}

void UIInputField::render(SDL_Point top_left) {
    cursor_visible.update();

    SDL_Rect viewport = ctx->viewport_from_layout(SDL_Rect{
	    top_left.x, top_left.y,
	    dims.first, dims.second,
	});

    text = Text(ctx->renderer, content + (cursor_visible.is_visible() ? "|" : ""), ctx->assets.fonts[font], color, viewport.w);
    auto [text_w, text_h] = text.get_size();

    // We scale the text to fill up the viewport 
    SDL_Rect text_target = SDL_Rect {0, 0, text_w, text_h};

    SDL_RenderSetViewport(ctx->renderer, &viewport);
    SDL_RenderCopy(ctx->renderer, text.get_texture(), NULL, &text_target);
}

void UIInputField::add_string(string s) {
    content += s;
}

void UIInputField::remove_character() {
    content.pop_back();
}

void UIInputField::clear() {
    content.clear();
}

UIDiary::UIDiary(shared_ptr<GraphicsContext> ctx)
    : ctx(ctx)
    , log(UIMessageLog(ctx, {LAYOUT_DIARY_LOG_RELATIVE.w, LAYOUT_DIARY_LOG_RELATIVE.h}))
    , input(UIInputField(ctx, Font::DIARY_FONT, {0x00, 0x00, 0x00, 0xFF}, {LAYOUT_DIARY_INPUT_RELATIVE.w, LAYOUT_DIARY_INPUT_RELATIVE.h}))
    , position(EaseOutExpoAnimation(LAYOUT_DIARY_HIDDEN_TOP_LEFT,
				    LAYOUT_DIARY_REVEALED_TOP_LEFT,
				    1.0))
    , revealed(true)
{
    position.start();
}

void UIDiary::set_revealed(bool reveal) {
    if(reveal == revealed) {
	return;
    }
    if(reveal) {
	position = EaseOutExpoAnimation(LAYOUT_DIARY_HIDDEN_TOP_LEFT, LAYOUT_DIARY_REVEALED_TOP_LEFT, 1.0);
    } else {
	position = EaseOutExpoAnimation(LAYOUT_DIARY_REVEALED_TOP_LEFT, LAYOUT_DIARY_HIDDEN_TOP_LEFT, 1.0);
    }
    position.start();
    ctx->play_sound(Sound::DIARY_SLIDE);

    revealed = reveal;
}

void UIDiary::render() {
    position.update();
    SDL_Point pos = position.get_current_state();

    SDL_Rect viewport = ctx->viewport_from_layout({pos.x, pos.y, LAYOUT_DIARY_DIMS.first, LAYOUT_DIARY_DIMS.second});

    SDL_RenderSetViewport(ctx->renderer, &viewport);
    SDL_RenderCopy(ctx->renderer, ctx->assets.textures[Texture::DIARY], NULL, NULL);

    log.render(SDL_Point{
	    pos.x + LAYOUT_DIARY_LOG_RELATIVE.x,
	    pos.y + LAYOUT_DIARY_LOG_RELATIVE.y
	});
    input.render(SDL_Point{
	    pos.x + LAYOUT_DIARY_INPUT_RELATIVE.x,
	    pos.y + LAYOUT_DIARY_INPUT_RELATIVE.y
	});
}
