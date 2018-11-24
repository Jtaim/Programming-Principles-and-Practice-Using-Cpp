// Written by Jtaim
// 8 Apr 2017
// Header file used for Programming: Principles and Practice Using C++ Second Edition
// section 6

#ifndef SECTION6_H	// begin header guard
#define SECTION6_H

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <forward_list>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

inline void clear_cin_buffer()
{
    std::cin.clear();
    // some compilers need this to show contents in rdbuf
    std::cin.sync_with_stdio(false);
    // check if buffer is empty
    auto cb = std::cin.rdbuf()->in_avail();
    std::cin.ignore(cb);  //clear buffer
}

// simple function to keep window console open
inline void keep_window_open()
{
    clear_cin_buffer();
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
