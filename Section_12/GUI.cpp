#include "GUI.h"
#include <sstream>

using namespace Graph_lib;

void Button::attach(Graph_lib::Window& win)
{
	pw = new Fl_Button(loc.x, loc.y, this->width, this->height, label.c_str());
	pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
	this->own = &win;
}

int In_box::get_int()
{
	Fl_Input& pi = reference_to<Fl_Input>(pw);
//	return atoi(pi.value());
	const char* p = pi.value();
	if(!isdigit(p[0])) return -999999;
	return atoi(p);
}

std::string In_box::get_string()
{
	Fl_Input& pi = reference_to<Fl_Input>(pw);
	return std::string(pi.value());
}

void In_box::attach(Graph_lib::Window& win)
{
	pw = new Fl_Input(loc.x, loc.y, this->width, this->height, label.c_str());
	this->own = &win;
}

void Out_box::put(int i)
{
	Fl_Output& po = reference_to<Fl_Output>(pw);
	std::stringstream ss;
	ss << i;
	po.value(ss.str().c_str());
}

void Out_box::put(const std::string& s)
{
	reference_to<Fl_Output>(pw).value(s.c_str());
}

void Out_box::attach(Graph_lib::Window& win)
{
	pw = new Fl_Output(loc.x, loc.y, this->width, this->height, label.c_str());
	this->own = &win;
}

int Menu::attach(Button& b)
{
	b.width = width;
	b.height = height;

	switch(k){
		case horizontal:
			b.loc = Point(loc.x + offset, loc.y);
			offset += b.width;
			break;
		case vertical:
			b.loc = Point(loc.x, loc.y + offset);
			offset += b.height;
			break;
	}
	selection.push_back(&b);
	return int(selection.size() - 1);
}

int Menu::attach(Button* p)
{
//	owned.push_back(p);
	return attach(*p);
}
