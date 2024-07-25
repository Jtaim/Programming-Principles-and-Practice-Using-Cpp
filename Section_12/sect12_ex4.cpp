/*
    Written by Jtaim
    7 July 2024
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 12 Exercise 4
    Draw a 3-by-3 tic-tac-toe board of alternating white and red squares.
*/

#include "Simple_window.hpp"
#include <print>

int main()
try
{
    using namespace GraphLib;

    Point top_left{ 100,100 };
    Simple_Window win{ top_left,600,400,"Exercise #4" };

    Point position{};
    std::vector<GraphLib::Rectangle> squares;
    for( int i{ 1 }; i <= 9; ++i )
    {
        if( i == 4 || i == 7 )
        {
            position.x = 0;
            position.y += 100;
        }
        Color::Color_Type wc = ( i % 2 ) ? Color::Color_Type::white : Color::Color_Type::red;
        GraphLib::Rectangle rectangle{ position, 100, 100 };
        rectangle.Set_Color( wc );
        rectangle.Set_Fill_Color( wc );
        squares.push_back( rectangle );
        position.x += 100;
    }

    for( auto &r : squares )
    {
        win.Attach( r );
    }

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
