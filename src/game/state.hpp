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

struct Item
{
	std::string name;
	std::string asset;
	std::string value;
};

struct Inventory
{
	std::vector<Item*> contents;
};

enum Scene
{
	TENT,
	DIGSITE,
};

struct State
{
	Scene scene;
	Inventory inventory;
	std::string track;
};


#endif /* STATE_HPP */
