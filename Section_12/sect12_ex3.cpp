/*
    Written by Jtaim
    Aug 4 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 12 Exercise 3
    Draw your initials 150 pixels high.
    Use a thick line.
    Draw each initial in a different color.
*/

#include "Simple_window.hpp"
#include <print>

int main()
try
{
    using namespace GraphLib;

    Point top_left{ 100,100 };
    Simple_Window win{ top_left,600,400,"Exercise #3" };

    Text first( Point( 200, 250 ), "J" );
    first.Set_Color( Color::Color_Type::red );
    first.Set_Font_Size( 150 );

    Text last( Point( 300, 250 ), "W" );
    last.Set_Color( Color::Color_Type::blue );
    last.Set_Font_Size( 150 );

    win.Attach( first );
    win.Attach( last );

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
