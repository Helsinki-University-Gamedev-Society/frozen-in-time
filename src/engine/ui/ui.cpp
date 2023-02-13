/*
 * =====================================================================================
 *
 *       Filename:  ui.cpp
 *
 *    Description:  ui definitions 
 *
 *        Version:  1.0
 *        Created:  02/13/2023 02:36:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include "ui.hpp"

using namespace UI;

std::string TestUI::Read()
{
	std::string input;
	std::cin >> input;
	return input;
}

void TestUI::Write(std::string text)
{
	std::cout << text;
}
