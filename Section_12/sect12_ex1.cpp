/*
    Written by Jtaim
    Aug 2 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 12 Exercise 1
    Draw a rectangle as a Rectangle and as a Polygon.
    Make the lines of the Polygon red and the lines of the Rectangle blue.
*/

#include "Simple_window.hpp"
#include "Window.hpp"
#include <print>

//void quit_cb( Fl_Widget *w, void *p );
int main()
try
{
    using namespace GraphLib;

    Point top_left{ 100,100 };
    Simple_Window win{ top_left,600,400,"Exercise #1" };

    GraphLib::Rectangle rectangle{ Point{100,100}, 100, 100 };
    rectangle.Set_Color( Color::Color_Type::blue );
    rectangle.Set_Fill_Color( Color::Color_Type::blue );
    win.Attach( rectangle );

    // define with namespace or ambiguous with Polygon in wingdi.h
    GraphLib::Polygon poly;
    poly.Add( Point{ 300,100 } );
    poly.Add( Point{ 400,100 } );
    poly.Add( Point{ 400,200 } );
    poly.Add( Point{ 300,200 } );
    poly.Set_Color( Color::Color_Type::red );
    poly.Set_Fill_Color( Color::Color_Type::red );
    win.Attach( poly );

    win.Wait_For_Button();
}
catch( std::exception &e )
{
    std::println( "exception: {}", e.what() );
    return 1;
}
catch( ... )
{
    std::println( "exception" );
    return 2;
}
