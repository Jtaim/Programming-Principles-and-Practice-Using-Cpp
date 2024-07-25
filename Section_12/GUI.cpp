#include "GUI.hpp"

using namespace GraphLib;

void Button::Attach( GraphLib::Window &win )
{
    pwidget = std::make_unique<Fl_Button>( location.x, location.y, this->width, this->height, label.c_str() );
    pwidget->callback( reinterpret_cast<Fl_Callback *>( widget_callback ), &win );  // pass the window
    this->own = &win;
}

int In_Box::get_int()
{
    Fl_Input &pi = reference_to<Fl_Input>( pwidget.get() );
    //	return atoi(pi.value());
    const std::string_view p = pi.value();
    if( !isdigit( p.at( 0 ) ) )
    {
        return std::numeric_limits<int>::min();
    }
    return atoi( p.data() );
}

std::string In_Box::get_string()
{
    Fl_Input &pi = reference_to<Fl_Input>( pwidget.get() );
    return std::string( pi.value() );
}

void In_Box::Attach( GraphLib::Window &win )
{
    pwidget = std::make_unique<Fl_Input>( location.x, location.y, this->width, this->height, label.c_str() );
    this->own = &win;
}

void Out_Box::put( int i )
{
    Fl_Output &po = reference_to<Fl_Output>( pwidget.get() );
    po.value( std::to_string( i ).c_str() );
}

void Out_Box::put( const std::string &s )
{
    reference_to<Fl_Output>( pwidget.get() ).value( s.c_str() );
}

void Out_Box::Attach( GraphLib::Window &win )
{
    pwidget = std::make_unique<Fl_Output>( location.x, location.y, this->width, this->height, label.c_str() );
    this->own = &win;
}

int Menu::Attach( Button &b )
{
    b.width = width;
    b.height = height;

    switch( kind )
    {
        case Kind::horizontal:
            b.location = Point( location.x + offset, location.y );
            offset += b.width;
            break;
        case Kind::vertical:
            b.location = Point( location.x, location.y + offset );
            offset += b.height;
            break;
    }
    selection.push_back( &b );
    return int( selection.Size() - 1 );
}

int Menu::Attach( Button *p )
{
    //	owned.push_back(p);
    return Attach( *p );
}
