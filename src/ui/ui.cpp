#include <SDL_keyboard.h>
#include <algorithm>
#include <iostream>
#include <memory>

#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>

#include "ui/animations.hpp"
#include "ui/assets.hpp"
#include "ui/ui.hpp"
#include "ui/ui_elements.hpp"

UI::UI(shared_ptr<GraphicsContext> ctx)
    : ctx(ctx)
    , inventory(UIInventory(ctx))
    , map(UIMap(ctx))
    , computer(UIComputer(ctx))
    , diary(UIDiary(ctx))
{
    inventory.add_item(Item::PICKAXE);
    inventory.add_item(Item::SHOVEL);
    inventory.add_item(Item::CHISEL);

    ctx->play_sound(Sound::DIARY_SCRIBBLE);
    ctx->play_sound(Sound::DIARY_SLIDE);

    SDL_StartTextInput();

    ctx->set_music_volume(0.05);
}

UI::~UI() {
    // SDL_DestroyWindow(window);
    SDL_Quit();

    SDL_StopTextInput();
}

void UI::update() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
	if(e.type == SDL_QUIT) {
	    events.push(UIEvent_EXIT{});
	}
	if(e.type == SDL_KEYDOWN) {
	    if(e.key.keysym.sym == SDLK_TAB) {
		current_story = current_story == Story::DIARY ? Story::COMPUTER : Story::DIARY;
		diary.set_revealed(current_story == Story::DIARY);
	    } else if(e.key.keysym.sym == SDLK_BACKSPACE) {
		if(current_story == Story::DIARY) {
		    diary.input.remove_character();
		} else {
		    computer.input.remove_character();
		}
	    } else if(e.key.keysym.sym == SDLK_RETURN) {
		string content;
		if(current_story == Story::DIARY) {
		    if(diary.input.get_content().empty()) {
			return;
		    }
		    content = diary.input.get_content();

		    diary.log.add_message("> " + content, Font::PAST_WRITING, 0.0);
		    diary.input.clear();
		} else {
		    if(computer.input.get_content().empty()) {
			return;
		    }
		    content = computer.input.get_content();

		    computer.log.add_message("> " + content, Font::PRESENT_PLAYER_SPEAKING, 0.0);
		    computer.input.clear();
		}
		events.push(UIEvent_SEND_COMMAND{current_story, content});

	    }
	} else if(e.type == SDL_TEXTINPUT) {
	    if(current_story == Story::DIARY) {
		diary.input.add_string(e.text.text);
	    } else {
		computer.input.add_string(e.text.text);
	    }
	}
    }
}

bool UI::poll(UIEvent *event) {
    if(events.empty()) {
	return false;
    } 

    *event = events.front();
    events.pop();

    return true;
}

void UI::write(Story story, string text) {
    Font font = story == Story::DIARY ? Font::PAST_WRITING : Font::PRESENT_NARRATION;
    write(story, text, font);
}

void UI::write(Story story, string text, double appear_time) {
    Font font = story == Story::DIARY ? Font::PAST_WRITING : Font::PRESENT_NARRATION;
    write(story, text, font, 0.0);
}

void UI::write(Story story, string text, Font font) {
    write(story, text, font, 0.0);
}

void UI::write(Story story, string text, Font font, double appear_time) {
    if(story == Story::DIARY) {
	ctx->play_sound(Sound::DIARY_SCRIBBLE);
	diary.log.add_message(text, font, appear_time);
    } else {
	computer.log.add_message(text, font, appear_time);
    }
}

void UI::play_sound(string name) {
    ctx->play_sound(name);
}

void UI::play_music(string name) {
    ctx->play_music(name);
}

void UI::set_map_image(string name) {
    map.set_texture(name);
}

void UI::add_inventory_item(string name) {
    inventory.add_item(name);
}

void UI::remove_inventory_item(string name) {
    inventory.remove_item(name);
}

void UI::render_background() {
    SDL_Rect viewport = ctx->viewport_from_layout(LAYOUT_BACKGROUND);

    SDL_RenderSetViewport(ctx->renderer, &viewport);
    SDL_RenderCopy(ctx->renderer, ctx->assets.get_texture(Texture::BACKGROUND), NULL, NULL);
}

void UI::render() {
    // Clear
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(ctx->renderer);

    // Do stuff
    render_background();

    computer.render();
    diary.render();
    map.render();
    inventory.render();

    // Present
    SDL_RenderPresent(ctx->renderer);

    // Delay to match the framerate
    int time_now = SDL_GetPerformanceCounter();
    double time_taken = (double) (time_now - time_since_last_render) / ((double) SDL_GetPerformanceFrequency());
    time_taken = time_taken < 0 ? 0 : time_taken; // Sometimes this is zero

    SDL_Delay(std::max(0.0, (1/fps - time_taken) * 1000));

    time_since_last_render = SDL_GetPerformanceCounter();
}

UI init_UI() {
    auto ctx = init_graphics();
    return UI(ctx);
}
