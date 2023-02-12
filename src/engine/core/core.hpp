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
