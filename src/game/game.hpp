#ifndef GAME_HPP
#define GAME_HPP

/*
 * =====================================================================================
 *
 *       Filename:  game.hpp
 *
 *    Description:  game definitions 
 *
 *        Version:  1.0
 *        Created:  02/13/2023 08:51:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "state.hpp"

class Game
{
	State state;
	std::string baseResponse;
	bool ExecuteBase(std::string command);
	std::string ExecuteTent(std::string command);
	std::string ExecuteDigSite(std::string command);
	std::string Execute(std::string command);
};


#endif /* GAME_HPP */
