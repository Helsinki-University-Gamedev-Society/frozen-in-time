/*
 * =====================================================================================
 *
 *       Filename:  sparser.cpp
 *
 *    Description:  sparser definitions 
 *
 *        Version:  1.0
 *        Created:  02/13/2023 12:19:30 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "sparser.hpp"

std::string Parser::parseTo(std::string from, std::string& to, std::string delim)
{
	std::size_t pos = from.find(delim);
	to.assign(from.substr(0,pos));

	return from.substr(pos+1);
};

