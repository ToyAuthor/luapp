/**
@file   Log.hpp
*/

#ifndef _LUAPP_LOG_HPP_
#define _LUAPP_LOG_HPP_

#include <cstdio>
#include <string>

namespace lua{
namespace log{


class Printer
{
	public:

		Printer(){}
		~Printer(){}

		const Printer& operator << (const int num) const
		{
			std::printf("%d",num);
			return *this;
		}

		const Printer& operator << (const float num) const
		{
			std::printf("%f",num);
			return *this;
		}

		const Printer& operator << (const double num) const
		{
			std::printf("%f",num);
			return *this;
		}

		const Printer& operator << (std::string str) const
		{
			std::printf("%s",str.c_str());
			return *this;
		}

		const Printer& operator << (std::wstring str) const
		{
			std::wprintf(L"%ls",str.c_str());
			return *this;
		}

		const Printer& operator << (std::string *str) const
		{
			std::printf("%s",str->c_str());
			return *this;
		}

		const Printer& operator << (std::wstring *str) const
		{
			std::wprintf(L"%ls",str->c_str());
			return *this;
		}

		const Printer& operator << (const Printer& (*func)(const Printer&)) const
		{
			return func(*this);
		}
};


inline const Printer& End(const lua::log::Printer& m)
{
	std::printf("\n");
	return m;
}

static ::lua::log::Printer      Cout;

}//namespace log
}//namespace lua

#endif//_LUAPP_LOG_HPP_
