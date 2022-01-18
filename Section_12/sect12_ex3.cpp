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

	Text first(Point(200, 250), "J");
	first.set_color(Color::Color_type::red);
	first.set_font_size(150);

	Text last(Point(300, 250), "W");
	last.set_color(Color::Color_type::blue);
	last.set_font_size(150);

	win.attach(first);
	win.attach(last);

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