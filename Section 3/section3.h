// Written by Jtaim
// 19 Sept 2015
// updated 1 Dec 2016
// Header file used for Programming: Principles and Practice Using C++ Second Edition
// section 3

#ifndef SECTION3_H     // begin header guard
#define SECTION3_H

#include<iostream>
#include<string>

void keep_window_open()
{
	std::cout << "\n\nEnter a char to exit.\n";
	char ch;
	std::cin >> ch;
}

// error function to be used (only) until error() is introduced in Chapter 5:
void simple_error(std::string s)	// write error: s and exit program
{
	std::cerr << "error: " << s << '\n';
	keep_window_open();
	exit(1);						// for some Windows environments
}
#endif              // close header guard
