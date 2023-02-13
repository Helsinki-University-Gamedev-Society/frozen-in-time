#ifndef UI_HPP
#define UI_HPP

/*
 * =====================================================================================
 *
 *       Filename:  ui.hpp
 *
 *    Description:  ui declarations 
 *
 *        Version:  1.0
 *        Created:  02/13/2023 02:34:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maroctamorg (mg), marcelogn.dev@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <string>

namespace UI
{
	class IUI
	{
		public:
		virtual ~IUI();

		virtual std::string Read();
		virtual void Write(std::string text);
	};

	class TestUI : public IUI
	{
		public:
		virtual std::string Read();
		virtual void Write(std::string text);
	};
}


#endif /* UI_HPP */
