// Written by Jtaim
// 8 Apr 2017
// Header file used for Programming: Principles and Practice Using C++ Second Edition
// section 6

#ifndef SECTION6_H	// begin header guard
#define SECTION6_H

#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>
#include <string>
#include <vector>

// simple function to keep window console open
inline void keep_window_open()
{
  std::cin.clear();
  std::cin.sync_with_stdio(false);
  std::cin.ignore(std::cin.rdbuf()->in_avail());  //clear buffer
  std::cout << "\nPress the Enter key to continue";
  std::cin.get();
}

inline void error(const std::string& s)
{
  throw std::runtime_error(s);
}

inline void error(const std::string& s, const std::string& s2)
{
  error(s + s2);
}

inline void error(const std::string& s, int i)
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
  if (static_cast<Source>(r) != a)
  {
    error("narrow_cast<>() failed");
  }
  return r;
}
#endif	// close header guard
