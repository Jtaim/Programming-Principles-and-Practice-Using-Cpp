// Written by Jtaim
// 8 Oct 2015
// updated 4 Dec 2016
// Header file used for Programming: Principles and Practice Using C++ Second Edition
// section 4

#ifndef SECTION4_H	// begin header guard
#define SECTION4_H

#include<iostream>
#include<string>

void keep_window_open()
{
	std::cout << "\n\nEnter something to exit.\n";
	std::cin.ignore(32765, '\n');
	std::cin.get();
}

// error function to be used (only) until error() is introduced in Chapter 5:
void simple_error(std::string s)	// write error: s and exit program
{
	std::cerr << "error: " << s << '\n';
	keep_window_open();
	exit(1);						// for some Windows environments
}
#endif	// close header guard
