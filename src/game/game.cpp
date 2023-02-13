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

#include "game.hpp"
#include "state.hpp"

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

void Game::ExecuteDigsite(Story story, std::string command) {
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
