/*
 * =====================================================================================
 *
 *       Filename:  sparser.hpp
 *
 *    Description:  sparser declarations 
 *
 *        Version:  1.0
 *        Created:  02/13/2023 12:20:49 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <string>
#include "../dl/dl.hpp"

class Sparser
{
	public:
	bool Load(Parser::Serialisable* sc, std::string filename);
	void Write(Parser::Serialisable* sc, std::string filename);
	void SaveState(std::string currentSceneLabel, Parser::Serialisable *inventory, std::string filename);
};

