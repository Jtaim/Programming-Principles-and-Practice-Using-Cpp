#ifndef WINDOW_GUARD
#define WINDOW_GUARD

#include "fltk.h"
#include "Point.h"
//#include "GUI.h"

#include <string>
#include <vector>

namespace Graph_lib
{

	class Shape;	// "forward declare" Shape
	class Widget;

	class Window : public Fl_Window
	{
	public:
		Window(int w, int h, const std::string& title);	// let the system pick the location
		Window(Point top_left, int w, int h, const std::string& title);
		virtual ~Window() {}

		int x_max() const { return width; }
		int y_max() const { return height; }

		void resize(int new_width, int new_height);

		void set_label(const std::string& title);
		std::string get_label() const { return std::string{label()}; }

		void attach(Shape& shape);
		void attach(Widget& widget);

		void detach(Shape& shape);			// remove s from shapes 
		void detach(Widget& widget);		// remove w from window (deactivate callbacks)

		void put_on_top(Shape& priority);	// put p on top of other shapes

	protected:
		void draw();

	private:
		std::string win_title;		// added this statement because FL_window class does not deep copy the title
		int width, height;			// window size
		std::vector<Shape*> shapes;	// shapes attached to window

		void init();
	};

	int gui_main();	// invoke GUI library's main event loop

	inline int x_max() { return Fl::w(); }	// width of screen in pixels
	inline int y_max() { return Fl::h(); }	// height of screen in pixels

} // Graph_lib
#endif // WINDOW_GUARD
