/*
 * =====================================================================================
 *
 *       Filename:  parser.cpp
 *
 *    Description:  parser util definitions 
 *
 *        Version:  1.0
 *        Created:  02/13/2023 05:36:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "parser.hpp"

std::string parseTo(std::string from, std::string& to, std::string delim)
{
	std::size_t pos = from.find(delim);
	to.assign(from.substr(0,pos));

	return from.substr(pos+1);
};


