// Written by Jtaim
// 2 Apr 2017
// Header file used for Programming: Principles and Practice Using C++ Second Edition
// section 5

#ifndef SECTION5_H	// begin header guard
#define SECTION5_H

#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<list>
#include<forward_list>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<array>
#include<regex>
#include<random>
#include<stdexcept>
#include <cstdlib>	// for rand() and srand()
#include <ctime>	// for time()
#include <utility>

#include<numeric>	// for MVS 2015 not under algorithm

inline void keep_window_open()
{
    std::cout << "\n\nhit enter key to exit.\n";
    std::cin.clear();
    std::cin.ignore(UINT8_MAX, '\n');
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
