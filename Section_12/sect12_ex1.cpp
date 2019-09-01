/*
	Written by Jtaim
	Aug 2 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 12 Exercise 1
	Draw a rectangle as a Rectangle and as a Polygon.
	Make the lines of the Polygon red and the lines of the Rectangle blue.
*/

#include "Simple_window.h"
#include "Graph.h"
#include "utility.h"

int main()
try{
	using namespace Graph_lib;

	Point top_left{100,100};
	Simple_window win{top_left,600,400,"Exercise #1"};

	Graph_lib::Rectangle r{Point{100,100}, 100, 100};	// top left corner, width, height
	r.set_color(Color::Color_type::blue);
	win.attach(r);

	Graph_lib::Polygon poly;	// define with namespace or ambiguous with Polygon in wingdi.h
	poly.add(Point{300,100});
	poly.add(Point{400,100});
	poly.add(Point{400,200});
	poly.add(Point{300,200});
	poly.set_color(Color::Color_type::red);
	win.attach(poly);

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