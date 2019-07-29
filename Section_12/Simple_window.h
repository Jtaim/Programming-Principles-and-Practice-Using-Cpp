#ifndef SIMPLE_WINDOW_GUARD
#define SIMPLE_WINDOW_GUARD

#include "GUI.h"	// for Simple_window only (doesn't really belong in Window.h)
#include <string>

// Simple_window is basic scaffolding for ultra-simple interaction with graphics
// it provides one window with one "next" button for ultra-simple animation

struct Simple_window: Graph_lib::Window
{
	Simple_window(Graph_lib::Point xy, int w, int h, const std::string& title);

	bool wait_for_button();

	Graph_lib::Button next_button;
private:
	bool button_pushed;

	static void cb_next(Graph_lib::Address, Graph_lib::Address addr) // callback for next_button
	//	{ reference_to<Simple_window>(addr).next(); }
	{
		static_cast<Simple_window*>(addr)->next();
	}

	void next();
};
#endif // SIMPLE_WINDOW_GUARD
