/*
 * =====================================================================================
 *
 *       Filename:  core.cpp
 *
 *    Description:  core engine functionality 
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

#include "core.hpp"
#include "actions/action.hpp"

Core::Core()
	: owns {true}
{
	dl = new DataLayer();
	sp = new Sparser();
	cp = new Cparser();
	ui = new UI::TestUI();
	ar = new Actions::ActionRegistrar();
}

Core::Core(DataLayer* _dl, Sparser* _sp, Cparser* _cp, UI* _ui, Actions::ActionRegistrar* ar)
	:	owns {false}, dl {_dl}, sp {_sp}, cp {_cp}, ui {_ui} {}

Core::~Core()
{
	for(auto action : actions)
	{
		delete action;
	}
	Dump();

	if(!owns) return;
	delete dl;
	delete sp;
	delete cp;
	delete ui;
	delete ar;
}

void Core::Dump()
{
	sp->Write(dl, DUMP_FILE);
}

void Core::DestroyDump()
{
	File::Delete(DUMP_FILE);
}

void Core::Save()
{
	sp->Write(&dl->currentScene, dl->currentScene.value.filename);
	sp->Write(&dl->bufferScene, dl->bufferScene.value.filename);
	sp->SaveState(dl->currentScene.label, &dl->inventory, STATE_FILE);
}

bool Core::LoadDump()
{
	bool success = sp->Load(dl, DUMP_FILE);
	DestroyDump();
	return success;
}

void Core::InitDataLayer()
{
	if(LoadDump()) return;

	//sp->LoadUGL(dl, UGL_FILE);
	sp->LoadState(dl, STATE_FILE);
	LoadAction(GLOBAL_SCENE).Execute();
}

void Core::Init()
{
	InitDataLayer();
}

void Core::ParseInput()
{
	cp->Parse(&command, ui->Read()); // blocking read method on ENTER
	GetAction(action, dl->MapToAction(command.Serialise()));
}

void Core::Execute()
{
	for(auto action : actions)
	{
		Action
	}
}

void Core::Loop()
{
	ParseInput();
	Execute();
	FlushUI();
}
