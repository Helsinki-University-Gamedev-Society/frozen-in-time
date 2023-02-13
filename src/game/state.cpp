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
#include "state.hpp"

std::string Inventory::List()
{
	return std::accumulate(contents.cbegin(), contents.cend(), "", [](Item* first, Item* second){ return first->name + ", " + second->name;});
}
