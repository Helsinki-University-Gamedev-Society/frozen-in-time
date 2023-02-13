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
#include "../ui/ui.hpp"

class Game
{
public:
	Game(UI* ui);
        void Execute(Story, std::string command);
private:
	State state;
	UI* ui;

	std::string baseResponse;
	
	bool ExecuteBase(std::string command);
	void ExecuteTent(std::string command);
    void ExecuteDigsite(std::string command);

	void ChangeScene(Scene scene);

    bool InventoryContains(string name);

};


#endif /* GAME_HPP */
