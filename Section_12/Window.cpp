#include "Window.h"
#include "GUI.h"

namespace Graph_lib
{

	Window::Window(int w, int h, const std::string& title)
		: Fl_Window{w, h, title.c_str()}, width{w}, height{h}
	{
		init();
	}

	Window::Window(Point top_left, int w, int h, const std::string& title)
		: Fl_Window{top_left.x, top_left.y, w, h, title.c_str()}, width{w}, height{h}
	{
		init();
	}

	void Window::init()
	{
		resizable(this);
		show();
	}

	//---------------------------------------------------- 

	void Window::draw()
	{
		Fl_Window::draw();
		for(const auto i : shapes){
			i->draw();
		}
		/*for(unsigned int i = 0; i < shapes.size(); ++i){
			shapes[i]->draw();
		}*/
	}

	void Window::attach(Widget& widget)
	{
		begin();				// FTLK: begin attaching new Fl_Wigets to this window
		widget.attach(*this);	// let the Widget create its Fl_Wigits
		end();					// FTLK: stop attaching new Fl_Wigets to this window
	}

	void Window::detach(Widget& button)
	{
		button.hide();
	}

	void Window::resize(int new_width, int new_height)
	{
		width = new_width;
		height = new_height;
		size(new_width, new_height);
	}

	void Window::attach(Shape& shape)
	{
		shapes.push_back(&shape);
//		s.attached = this;
	}
	void Window::detach(Shape& shape)
	{
		for(auto i{shapes.size()}; 0 < i; --i)	// guess last attached will be first released
			if(shapes[i - 1] == &shape)
				shapes.erase(shapes.begin() + (i - 1));//&shapes[i-1]);
	}


	void Window::put_on_top(Shape& priority)
	{
		for(size_t i{}; i < shapes.size(); ++i){
			if(&priority == shapes[i]){
				for(++i; i < shapes.size(); ++i){
					shapes.at(i - 1) = shapes[i];
				}
				shapes.at(shapes.size() - 1) = &priority;
				return;
			}
		}
	}

	int gui_main() { return Fl::run(); }

} // Graph_lib
