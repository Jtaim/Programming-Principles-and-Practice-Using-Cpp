// Written by Jtaim
// 19 Oct 2015
// updated 18 Dec 2016
// Header file used for Programming: Principles and Practice Using C++ Second Edition
// section 5

#ifndef SECTION5_H	// begin header guard
#define SECTION5_H

#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<list>
#include<forward_list>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<array>
#include<regex>
#include<random>
#include<stdexcept>
#include <cstdlib>	// for rand() and srand()
#include <ctime>	// for time()
#include <utility>

#include<numeric>	// for MVS 2015 not under algorithm

inline void keep_window_open()
{
	std::cout << "\n\nhit enter key to exit.\n";
	std::cin.clear();
	std::cin.ignore(32765, '\n');
	std::cin.get();
}

// error() simply disguises throws:
inline void error(const std::string &s)
{
	throw std::runtime_error(s);
}
#endif	// close header guard
