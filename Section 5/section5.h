// Written by Jtaim
// 19 Oct 2015
// Header file used for Programming: Principles and Practice Using C++ Second Edition
// section 5

#ifndef SECTION5_H     // begin header guard
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

#include<numeric> // for MVS 2015 not under algorithm

using namespace std;

inline void keep_window_open()
{
	cin.clear();
	cout << "Please enter a character to exit\n";
	char ch;
	cin >> ch;
	return;
}
// error() simply disguises throws:
inline void error(const string &s)
{
	throw runtime_error(s);
}
#endif              // close header guard