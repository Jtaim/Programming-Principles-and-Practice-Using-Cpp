// Written by Jtaim
// 22 Mar 2017
// Header file used for Programming: Principles and Practice Using C++ Second Edition
// section 3
// updated 18 May 2018
// added cstdlib

#pragma once

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<cstdlib>

// simple function to keep window console open
inline void keep_window_open()
{
	std::cout << "\n\nHit the Enter key to exit from " << __FILE__ << std::endl;
	std::cin.clear();
	std::cin.ignore(256, '\n');  //clear buffer
	std::cin.get();
}

// error function to be used (only) until error() is introduced in Chapter 5:
inline void simple_error(std::string s)	// write error: s and exit program
{
	std::cout << "error: " << s << std::endl;
	keep_window_open();
	std::exit(1);
}
