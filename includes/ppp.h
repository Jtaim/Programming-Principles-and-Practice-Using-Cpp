// Written by Jtaim
// 23 Nov 2018
// Header file used for Programming: Principles and Practice Using C++ Second Edition
// can use for all sections

#ifndef PROGRAMMING_PRINCIPLES_PRACTICE_H	// begin header guard
#define PROGRAMMING_PRINCIPLES_PRACTICE_H

#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <forward_list>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

/*  Some compilers need this set to false to show characters left in cin.rdbuf().
*   problem with doing this will lose synchronization between printf and cout if working with mixed functions.
*   Also need to declare start of program or before use of cin or risk reseting rdbuf() losing ptential wanted data.
*   See https://en.cppreference.com/w/cpp/io/ios_base/sync_with_stdio
*   Normally all C++ streams have this set to true. if is true then in_avail() is 0.*/

namespace ppp
{
	// simple function to keep window console open
	inline void keep_window_open()
	{
		std::cin.clear();
		std::cin.sync_with_stdio(false);
		std::cin.ignore(std::cin.rdbuf()->in_avail());	//clear cin buffer
		std::cout << "\nPress Enter key to continue";
		std::cin.get();
	}

	inline void error(const std::string s)
	{
		throw std::runtime_error(s);
	}

	inline void error(const std::string s, const std::string s2)
	{
		error(s + s2);
	}

	inline void error(const std::string s, int i)
	{
		std::ostringstream os;
		os << s << ": " << i;
		error(os.str());
	}

	// run-time checked narrowing cast (type conversion).
	template<typename Target, typename Source>
	Target narrow_cast(const Source& a)
	{
		auto r = static_cast<Target>(a);
		if(static_cast<Source>(r) != a){
			throw std::runtime_error("narrow_cast<>() failed");
		}
		return r;
	}
}

#endif	// close header guard
