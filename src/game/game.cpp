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

#include "../../include/game/cparser.hpp"
#include "../../include/game/game.hpp"
#include "../../include/state.hpp"

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

void Game::ChangeScene(Scene scene)
{
	if(scene == Scene::DIGSITE)
	{
		ui->write(state.story,
			"\"You step outside into the arctic air.\"");
		ui->write(state.story, "\"You are standing at an archaeological dig site. It is cold outside. Behind you, to the north, is the entrance to the main tent. On all other sides stretches the dig site surrounds you, with workers and junior scientists busy at work. Beyond your immediate vicinity are some smaller tents, mainly used as lodgings, as well as some vehicles, generators, and other necessities of an archaeological expedition.\"");
		ui->write(state.story, "\"Even further beyond, the arctic landscape of mid-spring King William Island stretches around you, before almost unnoticeably turning into sea-ice.\"");
		ui->write(state.story, "\"Fixing your eyes and thoughts once more unto the dig site itself, you spot a pickaxe, a shovel, and a chisel lying on and around some tables. Close to them, to your south, is the mound you have been investigating recently. Wrapped in a heavy winter coat, Dr. Blake Adams huddles around some maps laid out on a table. The entrance to the main tent stands to the north.\"");
		ui->write(state.story, "\"I should gather some tools and get to digging.\"", Font::PRESENT_PLAYER_THINKING);
		return;
	}

	if(scene == Scene::TENT && state.scene == Scene::DIGSITE)
	{
		ui->write(state.story, "\"You step back into the relative warmth of the main tent. There are some tables and chairs scattered around, with papers and files strewn all over the place. Dr. Gavin Graham is working on a computer in the corner. The tent’s exit is to your south.\"");
		return;
	}

	if(scene == Scene::TENT)
	{
		ui->write(state.story, "\"...but anyway, enough about the weather. We should probably get back to work. I gotta get back to this report, and I think you still have some digging to do out there. Can’t stretch that grant forever!\"", Font::PRESENT_OTHER_CHARACTER);
		ui->write(state.story, "\"I should get back to work. The tools should be somewhere around here, or maybe outside.\"", Font::PRESENT_PLAYER_THINKING);
		ui->write(state.story, "\"You are standing in a large tent. There are some tables and chairs scattered around, with papers and files strewn all over the place. Dr. Gavin Graham is working on a computer in the corner. The tent’s exit is to your south.\"");
		return;
	}
}

void Game::ExecuteTent(std::string command)
{
	string cmd = prettify_command(command);
	if(cmd == "look around")
	{
		ui->write(Story::COMPUTER, "\"You are standing in a large tent. There are some tables and chairs scattered around, with papers and files strewn all over the place. Dr. Gavin Graham is working on a computer in the corner. The tent’s exit is to your south.\"", Font::PRESENT_NARRATION);
		return;
	}
	if(cmd == "inspect computer")
	{
		ui->write(STORY::COMPUTER, "Gavin: \"Sorry C., I need the computer right now. Besides, you won’t need it to dig a hole.\"", Font::PRESENT_OTHER_CHARACTER);
		return;
	}
	if(cmd == "talk gavin")
	{
		ui->write(STORY::COMPUTER, "Gavin: \"Sorry C., but I really do need to finish this report. If you can’t find the tools they might be outside.\"", Font::PRESENT_OTHER_CHARACTER);
		return;
	}
	if(cmd == "go outside" || cmd == "go south")
	{
		ChangeScene(Scene::DIGSITE);
		return;
	}
	if(cmd == "go north" || cmd == "go east" || cmd == "go west")
	{
		ui->write(STORY::COMPUTER, "\"There is nothing in that direction.\"")
	}
	
	ui->write(STORY::COMPUTER, "\"I should not be thinking such insane thoughts right now.\"", Font::PRESENT_PLAYER_THINKING);
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
