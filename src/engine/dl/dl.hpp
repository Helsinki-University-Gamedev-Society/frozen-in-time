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

class UGL
{
	public:
	std::string label;
};

class Command
{
	public:
	UGL verb;
	UGL item1;
	UGL item2;
};

class Action
{
	public:
	
}

class Scene
{
	public:
	std::map<Command, Action>
};


class DataLayer
{
	// static section
	public:
	std::map<std::string, UGL> UGLDefinitions;
	Scene* GlobalScene;

	// stateful section
	Inventory Inventory;
	UGLLabel CurrentSceneLabel;

	// dynamic section
	Scene* CurrentScene;
	
	//DataLayer(UGLLabel currentScene);
	//~DataLayer();
};
