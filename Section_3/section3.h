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
    std::cin.clear();
    // check if buffer is empty
    auto cb = std::cin.rdbuf()->in_avail();
    if (cb) {
        std::cin.ignore(cb, '\n');  //clear buffer
    }
    std::cout << "\n\nHit the Enter key to exit" << std::endl;
    std::cin.get();
}

// error function to be used (only) until error() is introduced in Chapter 5:
inline void simple_error(std::string s)	// write error: s and exit program
{
    std::cout << "error: " << s << std::endl;
    keep_window_open();
    std::exit(1);
}
