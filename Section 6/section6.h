// Written by Jtaim
// 11 Nov 2015
// updated 21 Dec 2016
// Header file used for Programming: Principles and Practice Using C++ Second Edition
// section 6

#ifndef SECTION6_H     // begin header guard
#define SECTION6_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <list>
#include <forward_list>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <array>
#include <regex>
#include <random>
#include <stdexcept>
#include <cstdlib>	// for rand() and srand()
#include <ctime>	// for time()
#include <utility>
#include <cctype>

#include <numeric>	// for MVS 2015 not under algorithm

inline void keep_window_open()
{
	std::cout << "\n\nhit enter key to exit.\n";
	std::cin.clear();
	std::cin.ignore(INT16_MAX, '\n');
	std::cin.get();
}

inline void keep_window_open(const std::string s)
{
	if (s == "") return;
	std::cin.clear();
	std::cin.ignore(INT16_MAX, '\n');
	for (;;)
	{
		std::cout << "Please enter " << s << " to exit\n";
		std::string ss;
		while (std::cin >> ss && ss != s)
		{
			std::cout << "Please enter " << s << " to exit\n";
		}
		return;
	}
}

// error() simply disguises throws:
inline void error(const std::string &s)
{
	throw std::runtime_error(s);
}

#endif              // close header guard
