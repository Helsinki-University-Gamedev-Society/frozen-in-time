#ifndef CORE_HPP
#define CORE_HPP

/*
 * =====================================================================================
 *
 *       Filename:  core.hpp
 *
 *    Description:  core engine declarations
 *
 *        Version:  1.0
 *        Created:  02/11/2023 07:48:55 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <vector>
#include <functional>

#include "../global.hpp"
#include "../dl/dl.hpp"
#include "../sparser/sparser.hpp"
#include "../cparser/cparser.hpp"
#include "../ui/ui.hpp"


namespace Core 
{
	enum class ActionEnum // the parsing for this will be done by the sparser, should be defined in dl --> done once when loading, then makes all action look ups faster
	{
		UPDATE,
		INSERT,
		LOAD,
		WRITE
	};
	
	class Serialisable
	{
		public:
		virtual std::string Serialise();
		virtual void Deserialise(std::string from);
	};
	
	class Action : Serialisable
	{
		public:
		virtual void Execute();
	};
	
	class UpdateAction : Action
	{
		public:
		UpdateAction(std::string action);
		void Execute();
	}
	
	class ActionRegistrar
	{
		static const std::map<ActionEnum, std::function<Action*(std::string)>> Resolver = 
		{
			{ActionEnum::UPDATE, [](std::string x){return new UpdateAction(x);}}
		}; // we could play with constexpr containers to improve performance
		
		public:
		static void GetAction(Action* out, std::string action);
	};
	
	class Core
	{
		private:
		const bool owns;
		Command command;
		std::vector<Action*> action;
	
		private:
		DataLayer* dl;
		Sparser* sp;
		Cparser* cp;
		UI* ui;
	
		public:
		Core();
		Core(DataLayer* _dl, Sparser* _sp, Cparser* _cp, UI* _ui);
		~Core();
	
		private:
		void Dump();
		void Save();
	
		void InitDataLayer();
		void LoadDataLayer();
	
		void ParseInput();
		void Execute();
		void FlushUI();
	
		public:
		void Init();
		void Loop();
	};
}

#endif /* CORE_HPP */
