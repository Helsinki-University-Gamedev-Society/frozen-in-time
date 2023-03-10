/*
 * =====================================================================================
 *
 *       Filename:  state.cpp
 *
 *    Description:  state definitions 
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

#include <numeric>
#include <string>

#include "game/state.hpp"

std::string Inventory::List()
{
    if(contents.empty()) {
	return "You are not carrying anything right now!";
    }
    return std::accumulate(contents.cbegin(), contents.cend(), std::string(""), [](string acc, InvItem second){ return acc + ", " + second.name;});
}
