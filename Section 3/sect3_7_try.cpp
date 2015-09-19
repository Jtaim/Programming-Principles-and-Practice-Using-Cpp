//written by Jtaim
//date 18 Sept 2015
//Programming: Principles and Practice Using C++ Second Edition
/*
Section 3.7 try this exercise
*/

//#include "std_lib_facilities.h" //custom header
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;
inline void keep_window_open() { char ch; cin >> ch; }

//C++ programs start by executing the function main
int main()
{
	string s = "Goodbye, cruel world! ";
    cout << s << endl;
	keep_window_open();
	return 0;
}