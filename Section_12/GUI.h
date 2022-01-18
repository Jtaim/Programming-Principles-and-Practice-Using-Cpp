
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef GUI_GUARD
#define GUI_GUARD

#include "Window.h"
#include "Graph.h"

#include <string>

namespace Graph_lib
{

//------------------------------------------------------------------------------

	using Address = void*;    // Address is a synonym for void*
	using Callback = void(*)(Address, Address);    // FLTK's required function type for all callbacks

//------------------------------------------------------------------------------

	template<class W>
	W& reference_to(Address pw)
	// treat an address as a reference to a W
	{
		return *static_cast<W*>(pw);
	}

//------------------------------------------------------------------------------

	class Widget
	{
// Widget is a handle to an Fl_widget - it is *not* an Fl_widget
// We try to keep our interface classes at arm's length from FLTK
	public:
		Widget(Point xy, int w, int h, const std::string& s, Callback cb)
			: loc{xy}, width{w}, height{h}, label{s}, do_it{cb}, own{nullptr}, pw{nullptr}
		{}

		virtual void move(int dx, int dy) { hide(); pw->position(loc.x += dx, loc.y += dy); show(); }
		virtual void hide() { pw->hide(); }
		virtual void show() { pw->show(); }
		virtual void attach(Graph_lib::Window&) = 0;

		Point loc;
		int width;
		int height;
		std::string label;
		Callback do_it;

		virtual ~Widget() {}

		Widget& operator=(const Widget&) = delete;
		Widget& operator=(const Widget&&) = delete;
		Widget(const Widget&) = delete;

	protected:
		Graph_lib::Window* own;    // every Widget belongs to a Window
		Fl_Widget* pw;  // connection to the FLTK Widget
	};

//------------------------------------------------------------------------------

	struct Button: Widget
	{
		Button(Point xy, int w, int h, const std::string& label, Callback cb)
			: Widget(xy, w, h, label, cb)
		{}

		void attach(Graph_lib::Window& win) override;
	};

//------------------------------------------------------------------------------

	struct In_box: Widget
	{
		In_box(Point xy, int w, int h, const std::string& s)
			:Widget(xy, w, h, s, nullptr)
		{}
		int get_int();
		std::string get_string();

		void attach(Graph_lib::Window& win) override;
	};

//------------------------------------------------------------------------------

	struct Out_box: Widget
	{
		Out_box(Point xy, int w, int h, const std::string& s)
			:Widget(xy, w, h, s, 0)
		{}
		void put(int);
		void put(const std::string&);

		void attach(Graph_lib::Window& win) override;
	};

//------------------------------------------------------------------------------

	struct Menu: Widget
	{
		enum Kind { horizontal, vertical };
		Menu(Point xy, int w, int h, Kind kk, const std::string& label)
			: Widget(xy, w, h, label, 0), k(kk), offset(0)
		{}

		Vector_ref<Button> selection;
		Kind k;
		int offset;
		int attach(Button& b);      // Menu does not delete &b
		int attach(Button* p);      // Menu deletes p

		void show()                 // show all buttons
		{
			for(unsigned int i = 0; i < selection.size(); ++i){
				selection[i].show();
			}
		}
		void hide()                 // hide all buttons
		{
			for(unsigned int i = 0; i < selection.size(); ++i){
				selection[i].hide();
			}
		}
		void move(int dx, int dy)   // move all buttons
		{
			for(unsigned int i = 0; i < selection.size(); ++i){
				selection[i].move(dx, dy);
			}
		}

		void attach(Window& win)    // attach all buttons
		{
			for(int i = 0; i < selection.size(); ++i){
				win.attach(selection[i]);
			}
			own = &win;
		}
	};

//------------------------------------------------------------------------------

} // of namespace Graph_lib
#endif // GUI_GUARD
