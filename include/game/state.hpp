#ifndef STATE_HPP
#define STATE_HPP

/*
 * =====================================================================================
 *
 *       Filename:  state.hpp
 *
 *    Description:  state declarations
 *
 *        Version:  1.0
 *        Created:  02/13/2023 08:39:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <string>
#include <vector>

#include "../ui/ui.hpp"

struct InvItem
{
	std::string name;
	std::string asset;
	std::string value;
};

struct Inventory
{
	std::vector<InvItem> contents;
	std::string List();
};

enum Scene
{
	TENT,
	DIGSITE,
};

struct State
{
	Scene scene;
	Story story;
	Inventory inventory;
	std::string track;

        bool blake_talked_to = false;
};


#endif /* STATE_HPP */
