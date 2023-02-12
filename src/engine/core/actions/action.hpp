/*
 * =====================================================================================
 *
 *       Filename:  action.hpp
 *
 *    Description:  action declarations 
 *
 *        Version:  1.0
 *        Created:  02/12/2023 11:08:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <functional>
#include "entity.hpp"

namespace Actions
{
	class UpdateAction : Entity::Action
	{
		public:
		UpdateAction(std::string action) : Entity::Action(action) {};
		void Execute();
	};
	
	class ActionRegistrar
	{
		private:
		static const std::map<Entity::ActionEnum, std::function<Entity::Action*(std::string)>> Resolver;
		// we could play with constexpr containers to improve performance
		
		public:
		static void GetAction(Entity::Action* out, Entity::ActionEnum action);
		static void RegisterAction(Entity::ActionEnum, std::function<Entity::Action*(std::string)>);
	};
}	
