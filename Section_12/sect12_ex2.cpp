/*
    Written by Jtaim
    Aug 3 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 12 Exercise 2
    Draw a 100-by-30 Rectangle.
    Place the text “Howdy!” inside the Rectangle.

    https://graphicdesign.stackexchange.com/questions/4035/what-does-the-size-of-the-font-translate-to-exactly
*/

#include "Simple_window.hpp"
#include <print>

int main()
try
{
    using namespace GraphLib;

    const Point top_left{ 100,100 };
    Simple_Window win{ top_left,600,400,"Exercise #2" };

    const Point rectangle_location{ 250,185 };
    const int rectangle_width{ 100 };
    const int rectangle_height{ 30 };
    GraphLib::Rectangle rectangle{ rectangle_location, rectangle_width, rectangle_height };	// top left corner, width, height
    rectangle.Set_Color( Color::Color_Type::blue );
    rectangle.Set_Fill_Color( Color::Color_Type::blue );
    win.Attach( rectangle );

    float h{}, v{};
    Fl::screen_dpi( h, v );

    for( int font_size{ 10 }; font_size <= 40; font_size+=4 )
    {
        Text text_out{ rectangle_location, "Howdy" };
        text_out.Set_Font_Size( font_size );
        float pixel_height = text_out.Get_Font_Size() * h / 72;
        float new_location{ ( rectangle_height > pixel_height ) ? rectangle_height - pixel_height : pixel_height - rectangle_height };
        int new_y{ static_cast<int>( rectangle_height / 2.0f + new_location / 2.0f ) };
        text_out.Move( 2, new_y );
        text_out.Set_Color( Color::Color_Type::black );
        win.Attach( text_out );
        win.Redraw();
        win.Wait_For_Button();
        win.Detach( text_out );
    }

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
