/*
 * =====================================================================================
 *
 *       Filename:  entity.cpp
 *
 *    Description:  entity definitions 
 *
 *        Version:  1.0
 *        Created:  02/12/2023 10:08:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "entity.hpp"
#include <algorithm>

using namespace Entity;

bool Bitable::GetBit()
{
	return bit;	
}

void Bitable::SetBit(bool _bit)
{
	bit = _bit;
}

std::string Data::Serialise()
{
	return name + ":" + value;
}

std::string Data::Deserialise(std::string from)
{
	from = Parser::parseTo(from, name);
	return Parser::parseTo(from, value);
}

Item::Item(std::string from)
{
	Deserialise(from);
}

std::string Item::Serialise()
{
	return Data::Serialise() + ":" + asset;
}

std::string Item::Deserialise(std::string from)
{
	from = Data::Deserialise(from);
	return Parser::parseTo(from, asset);
}

std::string Command::Serialise()
{
	return command;
}

std::string Command::Deserialise(std::string from)
{
	return Parser::parseTo(from, command);
}

Action::Action(std::string action)
{
	Deserialise(action);
}

std::string Inventory::Serialise()
{
	std::string result {""};
	for(auto item : items)
	{
		result += item->Serialise() + "\n";
	}

	return result;
}

std::string Inventory::Deserialise(std::string from)
{
	std::string to;
	std::string from2;
	std::string to2;
	while((from = Parser::parseTo(from, to, "\n")).length() > 2)
	{
		from2 = to;
		while((from2 = Parser::parseTo(from2, to)).length() > 1)
		{
			items.push_back(new Entity<Item>(to2));
		}
	}

	return from;
}

std::string Scene::Serialise() const
{
	std::string result {""};
	result += filename
		+ delim
		+ data.Serialise()
		+ delim
		+ items.Serialise()
		+ delim;
	
	std::vector<std::string, std::string> commandStrings;
	std::for_each(mapCommandToAction.cbegin(), mapCommandToAction.cend(), [](std::pair<Entity<Command>, Entity<Action>>)
			{
				std::string command = item.first.Serialise();
				if(mapCommandToAction.find(command) != );
				}
			});

	for(auto commandString : commandStrings)
	{
		result += commandString + "\n\n";
	}

	return result;
}
