/*
 * =====================================================================================
 *
 *       Filename:  sparser.cpp
 *
 *    Description:  sparser definitions 
 *
 *        Version:  1.0
 *        Created:  02/13/2023 12:19:30 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "../utils/file_access/file_access.hpp"
#include "../utils/parser/parser.hpp"
#include "sparser.hpp"

bool Sparser::Load(Parser::Serialisable* sc, std::string filename)
{
	try
	{
		sc->Deserialise(File::Read(filename));	
		return true;
	}
	catch(std::exception ex)
	{
		return false;
	}
}

void Sparser::Write(Parser::Serialisable* sc, std::string filename)
{
	File::Write(sc->Serialise(), filename);
}

void Sparser::SaveState(std::string currentSceneLabel, Parser::Serialisable *inventory, std::string filename)
{
	File::Write(currentSceneLabel + "\n--\n" + inventory->Serialise(), filename);
}
