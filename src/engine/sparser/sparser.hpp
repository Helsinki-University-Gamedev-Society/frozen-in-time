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

namespace Parser
{
	std::string parseTo(std::string from, std::string& to, std::string delim = ":");

	class Serialisable
	{
		public:
		virtual std::string Serialise();
		virtual std::string Deserialise(std::string from);
		// returns leftover string to allow for chained deserialisation
	};

	class Sparser // totally unnecessary
	{

	};
}

