#include <iostream>
#include <vector>

#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>

#include "ui/animations.hpp"
#include "ui/ui_elements.hpp"
#include "ui/assets.hpp"
#include "ui/ui.hpp"

UIInventory::UIInventory(shared_ptr<GraphicsContext> ctx): ctx(ctx) {}

void UIInventory::add_item(Item item) {
    items.push_back(item);
}

void UIInventory::render() {
    if(items.empty()) {
	return;
    }

    SDL_Rect viewport = ctx->viewport_from_layout(LAYOUT_INVENTORY_CONTENTS);
    SDL_RenderSetViewport(ctx->renderer, &viewport);

    int cols = 1;
    int rows = 1;

    vector<vector<Item>> inv_rows;
    vector<Item> cur_row = vector<Item>{};

    int i;
    for(i = 0; i < items.size(); i++) {
	if(i % MAX_ITEMS_IN_ROW == 0 and i != 0) {
	    inv_rows.push_back(cur_row);
	    cur_row = vector<Item>{};
	    rows += 1;
	}
	cur_row.push_back(items[i]);
    }
    inv_rows.push_back(cur_row);

    cols = std::min(i, 5);

    int item_size = std::min(viewport.w / cols, viewport.h / rows);

    int top_left_y = 0;
    int rem_vert_padding = (viewport.h - inv_rows.size() * item_size) / inv_rows.size();

    for(const vector<Item>& inv_row : inv_rows) {
	top_left_y += rem_vert_padding / 2;

	int top_left_x = 0;
	int rem_hori_padding = (viewport.w - inv_row.size() * item_size) / inv_row.size();

	for(const Item& item : inv_row) {
	    top_left_x += rem_hori_padding / 2;

	    SDL_Rect target_rect = {top_left_x, top_left_y, item_size, item_size};
	    SDL_RenderCopy(ctx->renderer, ctx->assets.get_texture(ITEM_TO_TEXTURE.at(item)), NULL, &target_rect);

	    top_left_x += item_size;
	    top_left_x += rem_hori_padding / 2;
	}
	top_left_y += item_size;
	top_left_y += rem_vert_padding / 2;
    }
}

UIMap::UIMap(shared_ptr<GraphicsContext> ctx)
    : ctx(ctx)
    , texture_name(TEXTURE_TO_NAME.at(Texture::MAP)) {}

void UIMap::render() {
    SDL_Rect viewport = ctx->viewport_from_layout(LAYOUT_MAP);
    SDL_RenderSetViewport(ctx->renderer, &viewport);

    SDL_RenderCopy(ctx->renderer, ctx->assets.get_texture(texture_name), NULL, NULL);
}

void UIMap::set_texture(string name) {
    texture_name = name;
}

UIMessageLog::UIMessageLog(shared_ptr<GraphicsContext> ctx, Font font, SDL_Color color, pair<int, int> dims)
    : ctx(ctx)
    , font(font)
    , color(color)
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
    auto it = messages.rbegin();
	while(it != messages.rend()) {
	it->update();

	SDL_Texture *text_texture = it->get_current_texture();
	int text_w, text_h;
	SDL_QueryTexture(text_texture, NULL, NULL, &text_w, &text_h);

	SDL_Rect text_target{0, bottom_right_height - text_h, text_w, text_h};
	SDL_RenderCopy(ctx->renderer, text_texture, NULL, &text_target);

	bottom_right_height -= text_h;
	bottom_right_height -= LOG_MESSAGE_SPACING;

	++it;

	if(bottom_right_height < 0) {
	    // Remove messages that are too far up
	    messages.erase(messages.begin(), it.base());
	    break;
	}
    }
    
}

void UIMessageLog::add_message(string message) {
    auto animation = FadeInText(ctx, message, font, color, dims.first, 1.0);
    animation.start();

    messages.push_back(animation);
}

UIInputField::UIInputField(shared_ptr<GraphicsContext> ctx, Font font, SDL_Color color, pair<int, int> dims)
    : ctx(ctx)
    , font(font)
    , color(color)
    , content("")
    , text(Text(ctx->renderer, "", ctx->assets.get_font(font), color, dims.first))
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

    text = Text(ctx->renderer, content + (cursor_visible.is_visible() ? "|" : ""), ctx->assets.get_font(font), color, viewport.w);
    auto [text_w, text_h] = text.get_size();

    // We scale the text to fill up the viewport 
    SDL_Rect text_target = SDL_Rect {0, 0, text_w, text_h};

    SDL_RenderSetViewport(ctx->renderer, &viewport);
    SDL_RenderCopy(ctx->renderer, text.get_texture(), NULL, &text_target);
}

string UIInputField::get_content() {
    return content;
}

void UIInputField::add_string(string s) {
    content += s;
}

void UIInputField::remove_character() {
    if(not content.empty()) {
	content.pop_back();
    }
}

void UIInputField::clear() {
    content.clear();
}

UIDiary::UIDiary(shared_ptr<GraphicsContext> ctx)
    : ctx(ctx)
    , log(UIMessageLog(ctx, Font::DIARY_FONT, {0x00, 0x00, 0x00, 0xFF}, {LAYOUT_DIARY_LOG_RELATIVE.w, LAYOUT_DIARY_LOG_RELATIVE.h}))
    , input(UIInputField(ctx, Font::DIARY_FONT, {0x00, 0x00, 0x00, 0xFF}, {LAYOUT_DIARY_INPUT_RELATIVE.w, LAYOUT_DIARY_INPUT_RELATIVE.h}))
    , position(EaseOutExpoAnimation(LAYOUT_DIARY_HIDDEN_TOP_LEFT,
				    LAYOUT_DIARY_REVEALED_TOP_LEFT,
				    1.0))
    , revealed(false) {}

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
    SDL_RenderCopy(ctx->renderer, ctx->assets.get_texture(Texture::DIARY), NULL, NULL);

    log.render(SDL_Point{
	    pos.x + LAYOUT_DIARY_LOG_RELATIVE.x,
	    pos.y + LAYOUT_DIARY_LOG_RELATIVE.y
	});
    input.render(SDL_Point{
	    pos.x + LAYOUT_DIARY_INPUT_RELATIVE.x,
	    pos.y + LAYOUT_DIARY_INPUT_RELATIVE.y
	});
}

UIComputer::UIComputer(shared_ptr<GraphicsContext> ctx)
    : ctx(ctx)
    , log(UIMessageLog(ctx, Font::COMPUTER_FONT, {0xFF, 0xFF, 0xFF, 0xFF}, {LAYOUT_COMPUTER_LOG.w, LAYOUT_COMPUTER_LOG.h}))
    , input(UIInputField(ctx, Font::COMPUTER_FONT, {0xFF, 0xFF, 0xFF, 0xFF}, {LAYOUT_COMPUTER_INPUT.w, LAYOUT_COMPUTER_INPUT.h})) {}

void UIComputer::render() {
    log.render(SDL_Point{LAYOUT_COMPUTER_LOG.x, LAYOUT_COMPUTER_LOG.y});
    input.render(SDL_Point{LAYOUT_COMPUTER_INPUT.x, LAYOUT_COMPUTER_INPUT.y});
}
