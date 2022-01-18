// Written by Jtaim
// 22 Mar 2017
// Header file used for Programming: Principles and Practice Using C++ Second Edition
// section 3
// updated 18 May 2018
// added cstdlib

#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <format>

// simple function to keep window console open
inline void keep_window_open()
{
  std::cin.clear();
  std::cin.sync_with_stdio(false);
  std::cin.ignore(std::cin.rdbuf()->in_avail());  //clear buffer
  std::cout << "\nPress the Enter key to continue";
  std::cin.get();
}

// error function to be used (only) until error() is introduced in Chapter 5:
[[noreturn]] void simple_error(const std::string s)	// write error: s and exit program
{
  std::cout << std::format("error: {}", s) << std::endl;
  keep_window_open();
  std::exit(1);
}
