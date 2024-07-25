#pragma once

#include "fltk.hpp"
#include "Point.hpp"

#include <string>
#include <vector>

namespace GraphLib
{

    class Shape;	// "forward declare" Shape
    class Widget;

    class Window : protected Fl_Window
    {
    public:
        Window( int w, int h, const std::string &title = "" );	// let the system pick the location
        Window( Point top_left, int w, int h, const std::string &title = "" );
        virtual ~Window() {}

        int Get_Width() const;
        int Get_Height() const;
        void Resize( int new_width, int new_height );

        std::string Get_Label() const;
        void Set_Label( const std::string &s );

        void Attach( Shape &shape );
        void Attach( Widget &widget );
        void Detach( Shape &shape );			// remove s from shapes
        void Detach_Clear();                    // remove all shapes
        void Detach( Widget &widget );  		// remove w from window (deactivate callbacks)
        void Put_On_Top( Shape &priority ); 	// put p on top of other shapes

        void Fullscreen();
        void Fullscreen_Off();
        int Fullscreen_Active() const;
        void Resize( int x, int y, int w, int h );
        void Reposition( int x, int y );
    //protected:
        void Draw();
        void Show();
        void Hide();
        int Wait();
        void Redraw();

    private:
        int m_width, m_height;          // window size
        std::vector<Shape *> m_shapes;	// shapes attached to window

        void Init();
    };

    int gui_main();                     	// invoke GUI library's main event loop

    inline int Get_Width() { return Fl::w(); }	// width of screen in pixels
    inline int Get_Height() { return Fl::h(); }	// height of screen in pixels

} // GraphLib
