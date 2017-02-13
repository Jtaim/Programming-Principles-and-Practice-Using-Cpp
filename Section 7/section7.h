// Written by Jtaim
// 10 Dec 2015
// Updated 28 Dec 2016
// Header file used for Programming: Principles and Practice Using C++ Second Edition
// section 7

#ifndef SECTION7_H		// begin header guard
#define SECTION7_H

#include <iostream>
#include <string>
#include <stdexcept>

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

#endif	// close header guard
