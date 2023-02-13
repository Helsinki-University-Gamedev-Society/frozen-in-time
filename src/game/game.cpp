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

std::string Game::Execute(std::string command)
{
	if(!ExecuteBase(command)) return baseResponse;

	switch(state.scene)
	{
		case(Scene::TENT):
			return ExecuteTent(command);
			break;
		case(Scene::DIGSITE):
			return ExecuteDigSite(command);
			break;
		default:
			return "where the hell are you?";
	}
}
