/*
	Written by Jtaim
	Aug 4 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 12 Exercise 3
	Draw your initials 150 pixels high.
	Use a thick line.
	Draw each initial in a different color.
*/

#include "Simple_window.h"
#include "Graph.h"
#include "GUI.h"
#include "utility.h"

int main()
try{
	using namespace Graph_lib;

	Point top_left{100,100};
	Simple_window win{top_left,600,400,"Exercise #3"};

	Graph_lib::Polygon first_initial;	// define with namespace or ambiguous with Polygon in wingdi.h
	first_initial.add(Point{100,150});
	first_initial.add(Point{105,150});
	first_initial.add(Point{105,250});
	first_initial.add(Point{050,250});
	first_initial.add(Point{050,245});
	first_initial.add(Point{100,245});
	first_initial.set_color(Color::Color_type::red);
	first_initial.set_fill_color(Color::Color_type::red);
	win.attach(first_initial);

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