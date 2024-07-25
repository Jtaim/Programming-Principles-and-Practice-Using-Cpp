/*
    Written by Jtaim
    May 23 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 12 Drill 1
    Get an empty Simple_window with the size 600 by 400 and a label My window compiled, linked, and run.
    Note that you have to link the FLTK library as described in the README.md file;
    #include Graph.h and Simple_window.h in your code; and include Graph.cpp and Window.cpp in your project.

    Section 12 Drill 2
    add the examples from section 12.7 one by one, testing between each added subsection example.
*/

#include "Simple_window.hpp"
#include <print>

int main()
try
{
    using namespace GraphLib;

    Point top_left{ 100,100 };
    Simple_Window win{ top_left,600,400,"Canvas #1" };
    win.Fullscreen();
    win.Wait_For_Button();
    win.Fullscreen_Off();
    win.Resize( 0, 0, win.Get_Width(), win.Get_Height() );
    win.Reposition( top_left.x, top_left.y );
    int max_x{ win.Get_Width() - 40 };
    if( win.Fullscreen_Active() )
    {
        max_x = GraphLib::Get_Width() - 40;
    }
    Axis xa{ Axis::Orientation::x, Point{20, 300}, max_x, 10, "x axis" };
    xa.Set_Color( Color::Color_Type::black );
    win.Attach( xa );
    win.Set_Label( "Canvas #2" );
    win.Wait_For_Button();

    Axis ya{ Axis::Orientation::y, Point{20,300}, 280, 10, "y axis" };
    ya.Set_Color( Color::Color_Type::black );
    ya.label.Set_Color( Color::Color_Type::dark_red );
    win.Attach( ya );
    win.Set_Label( "Canvas #3" );
    win.Wait_For_Button();

    constexpr auto x_scale{ 15 };
    constexpr auto y_scale{ 50 };
    auto duration = static_cast<double>( max_x ) / x_scale;
    Function sine{ sin,0,duration,Point{20,150},1000,x_scale,y_scale };	// sine curve
    // plot sin() in the range [0:100) with (0,0) at (20,150)
    // using 1000 points; scale x values *50, scale y values *50
    win.Attach( sine );
    win.Set_Label( "Canvas #4" );
    win.Wait_For_Button();

    sine.Set_Color( Color::Color_Type::blue ); // change sine’s color

    GraphLib::Polygon poly;	// define with namespace or ambiguous with Polygon in wingdi.h
    poly.Add( Point{ 300,300 } );	// three points make a triangle
    poly.Add( Point{ 400,100 } );
    poly.Add( Point{ 500,300 } );
    poly.Set_Color( Color::Color_Type::red );
    poly.Set_Style( Line_Style::Line_Style_Type::dash );
    win.Attach( poly );
    win.Set_Label( "Canvas #5" );
    win.Wait_For_Button();

    GraphLib::Rectangle r{ Point{200,100}, 100, 100 };	// top left corner, width, height
    win.Attach( r );
    win.Set_Label( "Canvas #6" );
    win.Wait_For_Button();

    Closed_Polyline poly_rect;
    poly_rect.Add( Point{ 100,50 } );
    poly_rect.Add( Point{ 150,50 } );
    poly_rect.Add( Point{ 200,75 } );
    poly_rect.Add( Point{ 150,100 } );
    poly_rect.Add( Point{ 100,100 } );
    poly_rect.Add( Point{ 50,75 } );
    win.Attach( poly_rect );
    win.Wait_For_Button();

    r.Set_Fill_Color( Color::Color_Type::yellow );	// color the inside of the rectangle
    poly.Set_Style( Line_Style( Line_Style::Line_Style_Type::dash, 4 ) );
    poly_rect.Set_Style( Line_Style( Line_Style::Line_Style_Type::dash, 2 ) );
    poly_rect.Set_Fill_Color( Color::Color_Type::green );
    win.Set_Label( "Canvas #7" );
    win.Wait_For_Button();

    Text t{ Point{150,150}, "Hello, graphical world!" };
    win.Attach( t );
    win.Set_Label( "Canvas #8" );
    win.Wait_For_Button();

    t.Set_Font( Font::Font_Type::times_bold );
    t.Set_Font_Size( 20 );
    win.Set_Label( "Canvas #9" );
    win.Wait_For_Button();

    Image ii{ Point{100,50},"image.jpg" };	// 400x212-pixel jpg
    win.Attach( ii );
    win.Set_Label( "Canvas #10" );
    win.Wait_For_Button();

    ii.Move( 100, 200 );
    win.Set_Label( "Canvas #11" );
    win.Wait_For_Button();

    GraphLib::Circle c{ Point{100,200},50 };
    GraphLib::Ellipse e{ Point{100,200}, 75,25 };
    e.Set_Color( Color::Color_Type::dark_red );
    Mark m{ Point{100,200},'x' };
    win.Attach( c );
    win.Attach( e );
    win.Attach( m );

    Text sizes{ Point{100,20},
        std::format( "screen size: {}*{}; window size: {}*{}", Get_Width(), Get_Height(), win.Get_Width(), win.Get_Height() ) };
    win.Attach( sizes );

    Image cal{ Point{225,225},"snow_cpp.gif" };	// 320x240-pixel gif
    cal.Set_Mask( Point{ 40,40 }, 200, 150 );		// display center part of image
    win.Attach( cal );

    win.Set_Label( "Canvas #12" );
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
