#ifndef PARSER_HPP
#define PARSER_HPP

/*
 * =====================================================================================
 *
 *       Filename:  parser.hpp
 *
 *    Description:  parser util declarations
 *
 *        Version:  1.0
 *        Created:  02/13/2023 05:31:58 PM
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
		std::string delim {":"};
		virtual ~Serialisable();

		virtual std::string Serialise() const;
		virtual std::string Deserialise(std::string from);
		// returns leftover string to allow for chained deserialisation
	};
}

#endif /* PARSER_HPP */
