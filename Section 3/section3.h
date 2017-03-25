// Written by Jtaim
// 22 Mar 2017
// Header file used for Programming: Principles and Practice Using C++ Second Edition
// section 3

#ifndef SECTION3_H     // begin header guard
#define SECTION3_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>

// simple function to keep window console open
void keep_window_open()
{
	std::cout << "\n\nHit Enter key to exit.\n";
	std::cin.clear();
	std::cin.ignore(256, '\n');  //clear buffer
	std::cin.get();
}

// error function to be used (only) until error() is introduced in Chapter 5:
void simple_error(std::string s)	// write error: s and exit program
{
	std::cerr << "error: " << s << '\n';
	keep_window_open();
	exit(1);						// for some Windows environments
}
#endif              // close header guard
