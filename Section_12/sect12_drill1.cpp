/*
	Written by Jtaim
	May 23 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 12 Drill 1
	Get an empty Simple_window with the size 600 by 400 and a label My window compiled, linked, and run.
	Note that you have to link the FLTK library as described in the README.md file;
	#include Graph.h and Simple_window.h in your code; and include Graph.cpp and Window.cpp in your project.
*/

#include "Simple_window.h"
#include "Graph.h"

#include <iostream>
#include <stdexcept>

int main()
try{
	using namespace Graph_lib;

	Point top_left{100,100};

	Simple_window win{top_left,600,400,"My Window"};

	win.wait_for_button();

	return 0;
}
catch(std::exception& e){
	std::cerr << R"(exception: )" << e.what() << std::endl;
	return 1;
}
catch(...){
	std::cerr << R"(exception)";
	return 2;
}