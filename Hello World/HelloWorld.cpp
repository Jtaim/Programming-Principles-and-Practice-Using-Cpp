//Written by Jtaim
//Date 15 Sept 2015
//Programming: Principles and Practice Using C++ Second Edition

// simple hello world program

//#include "../std_lib_facilities.h"  // added the ../ because up a level from source files
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
	cout << "Hello, World!\n"		//output "Hello, World!"
	     << "Here we go again.\n";
	keep_window_open();			//wait for a character to be entered
	return 0;
}
