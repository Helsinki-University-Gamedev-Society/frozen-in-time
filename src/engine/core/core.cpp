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

Core::Core()
	: owns {true}
{
	dl = new DataLayer();
	sp = new Sparser();
	cp = new Cparser();
	ui = new UI();
}

Core::Core(DataLayer* _dl, Sparser* _sp, Cparser* _cp, UI* _ui)
	:	owns {false}, dl {_dl}, sp {_sp}, cp {_cp}, ui {_ui} {}

Core::~Core()
{
	delete action;
	Dump();

	if(!owns) return;
	delete dl, sp, cp, ui;
}

void Core::Dump()
{
	sp->FlushToFile(dl, DUMP_FILE);
}

void Core::Save()
{
	sp->WriteScene(dl->CurrentScene, dl->CurrentSceneLabel);
}

void Core::DestroyDump()
{
	File::Delete(DUMP_FILE);
}

bool Core::LoadDump()
{
	bool success = sp->LoadDump(dl, DUMP_FILE);
	DestroyDump();
	return success;
}

void Core::InitDataLayer()
{
	if(LoadDump()) return;

	sp->LoadUGL(dl, UGL_FILE);
	sp->LoadState(dl, STATE_FILE);
	LoadAction(GLOBAL_SCENE).Execute();
}

void Core::Init()
{
	InitDataLayer();
}

void Core::Prompt()
{

	
}

void Core::ParseInput()
{
	cp->Parse(&command, ui->Read()); // blocking read method on ENTER
	GetAction(action, dl->MapToAction(command.Serialise()));
}

void Core::Loop()
{
	ParseInput();
	Execute();
	FlushUI();
}
