/*
 * =====================================================================================
 *
 *       Filename:  dl.cpp
 *
 *    Description:  data layer access methods 
 *
 *        Version:  1.0
 *        Created:  02/10/2023 10:31:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "dl.hpp"

DataLayer::DataLayer() noexcept
	: entities {&ugl, &globalScene, &inventory, &currentScene, &bufferScene}{}

std::string DataLayer::Serialise()
{
	return ugl.Serialise()
		+ delim
		+ globalScene.Serialise()
		+ delim
		+ inventory.Serialise()
		+ delim
		+ currentScene.Serialise() 
		+ delim
		+ bufferScene.Serialise();
}

std::string DataLayer::Deserialise(std::string from)
{
	std::string to;
	for(int i{0}; i < entities.size() && (from = Parser::parseTo(from, to, delim)).length() > 4; i++)
	{
		entities[i]->Deserialise(to);
	}
	return from;
}
