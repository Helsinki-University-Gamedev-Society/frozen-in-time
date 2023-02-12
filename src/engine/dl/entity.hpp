#ifndef ENTITY_HPP
#define ENTITY_HPP

/*
 * =====================================================================================
 *
 *       Filename:  entity.hpp
 *
 *    Description:  entity declarations 
 *
 *        Version:  1.0
 *        Created:  02/12/2023 10:08:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <string>
#include <array>
#include <vector>
#include <map>

#include "../sparser/sparser.hpp"

namespace Entity
{
	class Bitable
	{
		private:
		bool bit {false};
	
		public:
		bool GetBit();
		void SetBit(bool bit);
	};

	template<typename T>
	struct Entity : Parser::Serialisable, Bitable
	{
		bool bit;
		std::string label;
		T value;
	
		Entity(std::string from)
		{
			static_assert(std::is_convertible<T*, Parser::Serialisable*>::value, "value must implement Parser::Serialisable interface");
			Deserialise(from);
		}
	
		std::string Serialise();
		std::string Deserialise(std::string from);
	};
	
	struct Data : Parser::Serialisable
	{
		std::string name;
		std::string value;
	
		std::string Serialise();
		std::string Deserialise(std::string from);
	};
	
	struct Item : Data
	{
		std::string asset;

		Item(std::string from);
	
		std::string Serialise();
		std::string Deserialise(std::string from);
	};
	
	class Command : Parser::Serialisable
	{
		public:
		std::string command;
		
		std::string Serialise();
		std::string Deserialise(std::string from);
	};
	
	enum class ActionEnum // the parsing for this will be done by the sparser, should be defined in dl --> done once when loading, then makes all action look ups faster
	{
		UPDATE,
		INSERT,
		LOAD,
		WRITE
	};
	
	class Action : Parser::Serialisable
	{
		public:
		ActionEnum action;
		std::string name;
		std::string parameters;

		Action(std::string action);
		virtual void Execute();
	};

	class Inventory : Parser::Serialisable
	{
		public:
		std::vector<Entity<Item>*> items;
		
		std::string Serialise();
		std::string Deserialise(std::string from);
	};
	
	class Scene : Parser::Serialisable
	{
		public:
		Inventory items;
		std::map<Entity<Command>, Entity<Action>> mapCommandToAction;
	};

	class UGL
	{
		public:
		std::map<std::string, std::string> synonyms;
		std::array<std::string, 100> ignore;
	};
}

#endif /* ENTITY_HPP */
