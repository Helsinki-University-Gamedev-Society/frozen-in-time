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
using namespace Entity;

struct DataLayer : Parser::Serialisable
{
	// static section
	UGL* ugl;
	Scene* globalScene;

	// stateful section
	Inventory inventory;

	// dynamic section
	Scene* currentScene;
	Scene* bufferScene;
};
