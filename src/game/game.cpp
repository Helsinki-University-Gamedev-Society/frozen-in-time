/*
 * =====================================================================================
 *
 *       Filename:  game.cpp
 *
 *    Description:  game file
 *
 *        Version:  1.0
 *        Created:  02/13/2023 08:49:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "game/cparser.hpp"
#include "game/game.hpp"
#include "game/state.hpp"

bool Game::InventoryContains(string name) {
    for(InvItem item : state.inventory.contents) {
	if(item.name == name) {
	    return true;
	}
    }
    return false;
}

Game::Game(UI* _ui)
	: ui {_ui}
{

}

bool Game::ExecuteBase(std::string command)
{
	if(command == "list")
	{
		ui->write(state.story, state.inventory.List());
		return true;
	}
}

void Game::ExecuteTent(std::string command) {

}

void Game::ExecuteDigsite(std::string command) {
    string cmd = prettify_command(command);

    if(cmd == "talk blake") {
	switch(state.blake_state) {
	    case BlakeState::UNSPOKEN_TO: {
		ui->write(Story::COMPUTER, "Blake: \"Oh hi C., back to work huh?\"", Font::PRESENT_OTHER_CHARACTER);
		ui->write(Story::COMPUTER, "\"Yeah, no rest for the wicked.\"", Font::PRESENT_PLAYER_SPEAKING);
		ui->write(Story::COMPUTER, "Blake: \"Tell me about it... You really think there's something in that mound? There are so many mounds just like that all over the island. What makes you think that one's anything special?\"", Font::PRESENT_OTHER_CHARACTER);
		ui->write(Story::COMPUTER, "\"Call it a hunch. I just have a feeling there's something there. And I never go against my instincts.\"", Font::PRESENT_PLAYER_SPEAKING);
		ui->write(Story::COMPUTER, "Blake: \"Well, you do you, C.\"", Font::PRESENT_OTHER_CHARACTER);
		break;
	    }
	    case BlakeState::GO_TO_WORK: {
		ui->write(Story::COMPUTER, "Blake: \"Shouldn't you be working? The tools should be out here somewhere.\"", Font::PRESENT_OTHER_CHARACTER);
		break;
	    }
	    case BlakeState::JOURNAL_FOUND: {
		ui->write(Story::COMPUTER, "\"I found these pages from a journal in the mound, what do you think?\"", Font::PRESENT_PLAYER_SPEAKING);
		ui->write(Story::COMPUTER, "Blake: \"Huh, there really was something down there... Good job!\"", Font::PRESENT_OTHER_CHARACTER);
		ui->write(Story::COMPUTER, "\"So, what do you think?\"", Font::PRESENT_PLAYER_SPEAKING);
		ui->write(Story::COMPUTER, "Blake: \"What do I think? I think you should read it.\"", Font::PRESENT_OTHER_CHARACTER);
		ui->write(Story::COMPUTER, "I should open the journal and read it.", Font::PRESENT_PLAYER_THINKING);
		break;
	    }
	}
    } else if(cmd == "take pickaxe") {
	if(not InventoryContains("pickaxe")) {
	    state.inventory.contents.push_back({"pickaxe", "item_pickaxe.png", ""});
	    ui->add_inventory_item("item_pickaxe.png");
	    ui->write(Story::COMPUTER, "This should come in handy.", Font::PRESENT_PLAYER_THINKING);

	    if(InventoryContains("shovel") and InventoryContains("chiselshovel")) {
		ui->write(Story::COMPUTER, "I think I have everything I need. Time to get to work.", Font::PRESENT_PLAYER_THINKING);
	    }
	} else {
	    ui->write(Story::COMPUTER, "You already have the pickaxe in your inventory!");
	}
    } else if(cmd == "take shovel") {
	if(not InventoryContains("shovel")) {
	    state.inventory.contents.push_back({"shovel", "item_shovel.png", ""});
	    ui->add_inventory_item("item_shovel.png");
	    ui->write(Story::COMPUTER, "This should come in handy.", Font::PRESENT_PLAYER_THINKING);

	    if(InventoryContains("pickaxe") and InventoryContains("chisel")) {
		ui->write(Story::COMPUTER, "I think I have everything I need. Time to get to work.", Font::PRESENT_PLAYER_THINKING);
	    }
	} else {
	    ui->write(Story::COMPUTER, "You already have the shovel in your inventory!");
	}
    } else if(cmd == "take chisel") {
	if(not InventoryContains("chisel")) {
	    state.inventory.contents.push_back({"shovel", "item_chisel.png", ""});
	    ui->add_inventory_item("item_chisel.png");
	    ui->write(Story::COMPUTER, "This should come in handy.", Font::PRESENT_PLAYER_THINKING);

	    if(InventoryContains("pickaxe") and InventoryContains("shovel")) {
		ui->write(Story::COMPUTER, "I think I have everything I need. Time to get to work.", Font::PRESENT_PLAYER_THINKING);
	    }
	} else {
	    ui->write(Story::COMPUTER, "You already have the chisel in your inventory!");
	}
    } else if(cmd == "inspect mound") {
	ui->write(Story::COMPUTER, "Okay, let's take a look at this... Seems to be some dirt on top.", Font::PRESENT_PLAYER_THINKING);
    } else if(cmd == "use pickaxe") {
	if(state.mound_material == MoundMaterial::ROCK) {
	    ui->write(Story::COMPUTER, "Aha, that's done the trick!", Font::PRESENT_PLAYER_THINKING);
	    state.mound_material = MoundMaterial::PERMAFROST;
	    ui->write(Story::COMPUTER, "The rock has been removed, revealing some permafrost underneath.", Font::PRESENT_NARRATION);
	} else {
	    ui->write(Story::COMPUTER, "Hmm... No, that didn't work. I should try something else.", Font::PRESENT_PLAYER_THINKING);
	}
    } else if(cmd == "use shovel") {
	if(state.mound_material == MoundMaterial::DIRT) {
	    ui->write(Story::COMPUTER, "Aha, that's done the trick!", Font::PRESENT_PLAYER_THINKING);
	    state.mound_material = MoundMaterial::ROCK;
	    ui->write(Story::COMPUTER, "The rock has been removed, revealing a rock underneath.", Font::PRESENT_NARRATION);
	} else {
	    ui->write(Story::COMPUTER, "Hmm... No, that didn't work. I should try something else.", Font::PRESENT_PLAYER_THINKING);
	}
    } else if(cmd == "use chisel") {
	if(state.mound_material == MoundMaterial::PERMAFROST) {
	    ui->write(Story::COMPUTER, "Aha, that's done the trick!", Font::PRESENT_PLAYER_THINKING);
	    state.mound_material = MoundMaterial::NONE;
	    ui->write(Story::COMPUTER, "That's it! Now what do we have here?", Font::PRESENT_PLAYER_THINKING);
	    ui->write(Story::COMPUTER, "At the bottom of the hole are some scraps of paper. As you carefully investigate them, you realise they are loose pages from some kind of a journal.", Font::PRESENT_NARRATION);
	    ui->write(Story::COMPUTER, "This could be huge! I should probably open the journal to find out more. After all, if it isn't anything interesting, or I want to do something else, I can always close the journal.", Font::PRESENT_PLAYER_THINKING);
	    state.blake_state = BlakeState::JOURNAL_FOUND;
	} else {
	    ui->write(Story::COMPUTER, "Hmm... No, that didn't work. I should try something else.", Font::PRESENT_PLAYER_THINKING);
	}
    } else if(cmd == "look") {
	ui->write(Story::COMPUTER,
		  "Fixing your eyes and thoughts once more unto the dig site itself, you spot a pickaxe, a shovel, and a chisel lying on and around some tables. "
		  "Close to them, to your south, is the mound you have been investigating recently. Wrapped in a heavy winter coat, Dr. Blake Adams huddles around some maps laid out on a table. "
		  "The entrance to the main tent stands to the north.",
		  Font::PRESENT_NARRATION);
    }
}

void Game::Execute(Story story, std::string command)
{
    // if(!ExecuteBase(command)) return baseResponse;
    ExecuteDigsite(command);
    return;

	switch(state.scene)
	{
		case(Scene::TENT):
			return ExecuteTent(command);
			break;
		case(Scene::DIGSITE):
		        return ExecuteDigsite(command);
			break;
		default:
		        break;
	}
}
