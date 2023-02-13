/*
 * =====================================================================================
 *
 *       Filename:  file_access.hpp
 *
 *    Description:  file access defintions stub
 *
 *        Version:  1.0
 *        Created:  02/13/2023 05:12:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _FILE_ACCESS_
#define _FILE_ACCESS_

#include <filesystem>
#include <string>

using std::string;

class File
{
	public:
    static void SetPath(string path);
    static void ResetPath();

    static string GetFullPath(string relative_path);
    static string Read(string path);
	
	static void Write(string path, string constant);
	static void Delete(string path);
};

#endif // _FILE_ACCESS_
