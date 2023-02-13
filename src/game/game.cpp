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

void Game::ExecuteTent(std::string command)
{

}

string Game::ExecuteDigsite(Story story, std::string command) {
    string cmd = prettify_command(command);

    if(cmd == "talk blake") {
	if(not state.blake_talked_to) {
	    ui->write(Story::COMPUTER, "Blake: \"Oh hi C., back to work huh?\"", Font::PRESENT_OTHER_CHARACTER);
	    ui->write(Story::COMPUTER, "\"Yeah, no rest for the wicked.\"", Font::PRESENT_PLAYER_SPEAKING);
	    ui->write(Story::COMPUTER, "Blake: \"Tell me about it… You really think there’s something in that mound? There are so many mounds just like that all over the island. What makes you think that one’s anything special?\"", Font::PRESENT_OTHER_CHARACTER);
	    ui->write(Story::COMPUTER, "\"Call it a hunch. I just have a feeling there’s something there. And I never go against my instincts.\"", Font::PRESENT_PLAYER_SPEAKING);
	    ui->write(Story::COMPUTER, "Blake: \"Well, you do you, C.\"", Font::PRESENT_OTHER_CHARACTER);
	} else {
	    ui->write(Story::COMPUTER, "Shouldn’t you be working? The tools should be out here somewhere.", Font::PRESENT_OTHER_CHARACTER);
	}
    } else if(cmd == "take pickaxe") {
	if(not InventoryContains("pickaxe")) {
	    state.inventory.contents.push_back({"pickaxe", "item_pickaxe.png", ""});
	    ui->write(Story::COMPUTER, "This should come in handy.");

	    if(InventoryContains("pickaxe") and InventoryContains("shovel")) {
		ui->write(Story::COMPUTER, "I think I have everything I need. Time to get to work.");
	    }
	} else {
	    ui->write(Story::COMPUTER, "You already have the pickaxe in your inventory!");
	}
    } else if(cmd == "take shovel") {
	if(not InventoryContains("shovel")) {
	    state.inventory.contents.push_back({"shovel", "item_shovel.png", ""});
	    ui->write(Story::COMPUTER, "This should come in handy.");

	    if(InventoryContains("pickaxe") and InventoryContains("shovel")) {
		ui->write(Story::COMPUTER, "I think I have everything I need. Time to get to work.");
	    }
	} else {
	    ui->write(Story::COMPUTER, "You already have the shovel in your inventory!");
	}
    } else if(cmd == "take chisel") {
	if(not InventoryContains("chisel")) {
	    state.inventory.contents.push_back({"shovel", "item_chisel.png", ""});
	    ui->write(Story::COMPUTER, "This should come in handy.");

	    if(InventoryContains("pickaxe") and InventoryContains("shovel")) {
		ui->write(Story::COMPUTER, "I think I have everything I need. Time to get to work.");
	    }
	} else {
	    ui->write(Story::COMPUTER, "You already have the chisel in your inventory!");
	}
    }
}

std::string Game::Execute(Story story, std::string command)
{
	if(!ExecuteBase(command)) return baseResponse;

	switch(state.scene)
	{
		case(Scene::TENT):
			return ExecuteTent(command);
			break;
		case(Scene::DIGSITE):
		        return ExecuteDigsite(story, command);
			break;
		default:
			return "where the hell are you?";
	}
}
