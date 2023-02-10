#include <SDL_render.h>

#include "ui/ui_elements.hpp"
#include "ui/assets.hpp"
#include "ui/ui.hpp"

UIInventory::UIInventory(shared_ptr<AssetManager> assets, int items_hori):
    assets(assets), items_hori(items_hori) {}

void UIInventory::add_item(Item item) {
    items.push_back(item);
}

void UIInventory::render(SDL_Renderer *renderer, SDL_Rect viewport) {
    SDL_RenderSetViewport(renderer, &viewport);
    int item_size = viewport.w / items_hori;

    int row = 0;
    int col = 0;

    SDL_Rect target_rect;
    for(const Item& item : items) {
	target_rect = {col * item_size, row * item_size,
		       item_size, item_size};

	SDL_RenderCopy(renderer, assets->textures[ITEM_TO_TEXTURE.at(item)], NULL, &target_rect);

	++col;
	if(col > items_hori) {
	    col = 0;
	    ++row;
	}
    }
}
