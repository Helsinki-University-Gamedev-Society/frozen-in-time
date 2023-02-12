/*
 * =====================================================================================
 *
 *       Filename:  action.cpp
 *
 *    Description:  action definitions
 *
 *        Version:  1.0
 *        Created:  02/12/2023 11:14:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "action.hpp"
#include <entity.hpp>

using namespace Actions;

ActionRegistrar::GetAction(Entity::Action* out, std::string action)
{
	Resolver.insert(std::pair<Entity::ActionEnum, std::function<Entity::Action*(std::string)>>{Entity::ActionEnum::UPDATE, [](std::string x){return new UpdateAction(x);}});
}
