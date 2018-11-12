// Written by Jtaim
// 9 Apr 2017
// Header file used for Programming: Principles and Practice Using C++ Second Edition
// section 7

#ifndef SECTION7_H	// begin header guard
#define SECTION7_H

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
#include <utility>

#include<numeric>	// for MVS 2015 not under algorithm

// simple function to keep window console open
inline void keep_window_open()
{
    std::cin.clear();
    // some compilers need this to show contents in rdbuf
    std::cin.sync_with_stdio(false);
    // check if buffer is empty
    auto cb = std::cin.rdbuf()->in_avail();
    std::cin.ignore(cb);  //clear buffer
    std::cout << "\n\nHit the Enter key to exit" << std::endl;
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
    if (static_cast<Source>(r) != a) {
        error("narrow_cast<>() failed");
    }
    return r;
}
#endif	// close header guard
