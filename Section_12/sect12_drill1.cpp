/*
	Written by Jtaim
	May 23 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 12 Drill 1
	Get an empty Simple_window with the size 600 by 400 and a label My window compiled, linked, and run.
	Note that you have to link the FLTK library as described in Appendix D;
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

	Simple_window win{top_left,600,400,"Canvas"};

	Graph_lib::Polygon poly;

	poly.add(Point{300,200});
	poly.add(Point{350,100});
	poly.add(Point{400,200});

	poly.set_color(Color::Color_type::red);

	win.attach(poly);

	win.wait_for_button();

	return 0;
}
catch(std::exception& e){
	std::cerr << R"(exception: )" << e.what() << std::endl;
	//ppp::keep_window_open();
	return 1;
}
catch(...){
	std::cerr << R"(exception)";
	//ppp::keep_window_open();
	return 2;
}