// Written by Jtaim
// 11 Nov 2015
// Header file used for Programming: Principles and Practice Using C++ Second Edition
// section 6

#ifndef SECTION6_H     // begin header guard
#define SECTION6_H

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
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <utility>

#include<numeric> // for MVS 2015 not under algorithm

using namespace std;

inline void keep_window_open()
{
	cin.clear();
	cin.ignore(INT8_MAX, '\n');
	cout << "Please enter a character to exit\n";
	char ch;
	cin >> ch;
	return;
}
inline void keep_window_open(string s)
{
	if (s == "") return;
	cin.clear();
	cin.ignore(120, '\n');
	for (;;) {
		cout << "Please enter " << s << " to exit\n";
		string ss;
		while (cin >> ss && ss != s)
			cout << "Please enter " << s << " to exit\n";
		return;
	}
}
// error() simply disguises throws:
inline void error(const string &s)
{
	throw runtime_error(s);
}
#endif              // close header guard