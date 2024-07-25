/*
    Written by Jtaim
    May 23 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 12 Drill 1
    Get an empty Simple_window with the size 600 by 400 and a label My window compiled, linked, and run.
    Note that you have to link the FLTK library as described in the README.md file;
    #include Graph.h and Simple_window.h in your code; and include Graph.cpp and Window.cpp in your project.
*/

#include "Simple_window.hpp"

#include <print>

int main()
try
{
    GraphLib::Point top_left{ 100, 100 };
    Simple_Window win{ top_left, 600, 400, "My Window" };
    GraphLib::Polygon poly{ { 300,200 }, { 350,100 }, { 400,200 } };
    poly.Set_Color( GraphLib::Color::Color_Type::red );
    win.Attach( poly );
    win.Wait_For_Button();
    return 0;
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
