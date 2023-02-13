#ifndef DL_HPP
#define DL_HPP

/*
 * =====================================================================================
 *
 *       Filename:  dl.hpp
 *
 *    Description:  data layer declaration  
 *
 *        Version:  1.0
 *        Created:  02/10/2023 10:31:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <map>
#include <string>

#include "entity.hpp"

struct DataLayer : Parser::Serialisable
{
	private:
	const std::string delim {"\n----\n"};
	const std::array<Parser::Serialisable*, 5> entities;

	public:
	// static section
	Entity::Entity<Entity::UGL> ugl;
	Entity::Entity<Entity::Scene> globalScene;

	// stateful section
	Entity::Entity<Entity::Inventory> inventory;

	// dynamic section
	Entity::Entity<Entity::Scene> currentScene;
	Entity::Entity<Entity::Scene> bufferScene;

	DataLayer() noexcept;

	std::string Serialise();
	std::string Deserialise(std::string from);

	//template <typename T>
	//Entity::Entity<T>& operator[](std::string label);
};

#endif /* DL_HPP */
