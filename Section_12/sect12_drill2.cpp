/*
	Written by Jtaim
	May 23 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 12 Drill 1
	Get an empty Simple_window with the size 600 by 400 and a label My window compiled, linked, and run.
	Note that you have to link the FLTK library as described in the README.md file;
	#include Graph.h and Simple_window.h in your code; and include Graph.cpp and Window.cpp in your project.

	Section 12 Drill 2
	add the examples from section 12.7 one by one, testing between each added subsection example.
*/

#include "Simple_window.h"
#include "Graph.h"
#include "utility.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

int main()
try{
	using namespace Graph_lib;

	Point top_left{100,100};

	Simple_window win{top_left,600,400,"My Window"};
	win.wait_for_button();
	
	Axis xa{Axis::Orientation::x, Point{20, 300}, 280, 10, "x axis"};
	xa.set_color(Color::Color_type::black);
	win.attach(xa);
	win.set_label("Canvas #2");
	win.wait_for_button();

	Axis ya{Axis::Orientation::y, Point{20,300}, 280, 10, "y axis"};
	ya.set_color(Color::Color_type::cyan);
	ya.label.set_color(Color::Color_type::dark_red);
	win.attach(ya);
	win.set_label("Canvas #3");
	win.wait_for_button();

	Function sine{sin,0,100,Point{20,150},1000,50,50};	// sine curve
	// plot sin() in the range [0:100) with (0,0) at (20,150)
	// using 1000 points; scale x values *50, scale y values *50
	win.attach(sine);
	win.set_label("Canvas #4");
	win.wait_for_button();

	sine.set_color(Color::Color_type::blue); // change sine’s color

	Graph_lib::Polygon poly;	// define with namespace or ambiguous with Polygon in wingdi.h
	poly.add(Point{300,200});	// three points make a triangle
	poly.add(Point{350,100});
	poly.add(Point{400,200});
	poly.set_color(Color::Color_type::red);
	poly.set_style(Line_style::Line_style_type::dash);
	win.attach(poly);
	win.set_label("Canvas #5");
	win.wait_for_button();

	Graph_lib::Rectangle r{Point{200,200}, 100, 50};	// top left corner, width, height
	win.attach(r);
	win.set_label("Canvas #6");
	win.wait_for_button();

	Closed_polyline poly_rect;
	poly_rect.add(Point{100,50});
	poly_rect.add(Point{200,50});
	poly_rect.add(Point{200,100});
	poly_rect.add(Point{100,100});
	poly_rect.add(Point{50,75});
	win.attach(poly_rect);
	win.wait_for_button();

	r.set_fill_color(Color::Color_type::yellow);	// color the inside of the rectangle
	poly.set_style(Line_style(Line_style::Line_style_type::dash, 4));
	poly_rect.set_style(Line_style(Line_style::Line_style_type::dash, 2));
	poly_rect.set_fill_color(Color::Color_type::green);
	win.set_label("Canvas #7");
	win.wait_for_button();

	Text t{Point{150,150}, "Hello, graphical world!"};
	win.attach(t);
	win.set_label("Canvas #8");
	win.wait_for_button();

	t.set_font(Font::Font_type::times_bold);
	t.set_font_size(20);
	win.set_label("Canvas #9");
	win.wait_for_button();

	Image ii{Point{100,50},"image.jpg"};	// 400x212-pixel jpg
	win.attach(ii);
	win.set_label("Canvas #10");
	win.wait_for_button();

	ii.move(100, 200);
	win.set_label("Canvas #11");
	win.wait_for_button();

	Graph_lib::Circle c{Point{100,200},50};
	Graph_lib::Ellipse e{Point{100,200}, 75,25};
	e.set_color(Color::Color_type::dark_red);
	Mark m{Point{100,200},'x'};
	win.attach(c);
	win.attach(e);
	win.attach(m);

	std::ostringstream oss;
	oss << "screen size: " << x_max() << "*" << y_max()
		<< "; window size: " << win.x_max() << "*" << win.y_max();
	Text sizes{Point{100,20},oss.str()};
	win.attach(sizes);

	Image cal{Point{225,225},"snow_cpp.gif"};	// 320x240-pixel gif
	cal.set_mask(Point{40,40}, 200, 150);		// display center part of image
	win.attach(cal);

	win.set_label("Canvas #12");
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