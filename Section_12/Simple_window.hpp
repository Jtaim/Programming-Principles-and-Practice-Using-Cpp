#pragma once

#include "GUI.hpp"	// for Simple_window only (doesn't really belong in Window.h)
#include <string>

// Simple_window is basic scaffolding for ultra-simple interaction with graphics
// it provides one window with one "next" button for ultra-simple animation

struct Simple_Window : GraphLib::Window
{
    Simple_Window( GraphLib::Point xy, int w, int h, const std::string &title )
        : Window( xy, w, h, title ),
        button_pushed( false ),
        next_button( GraphLib::Point( Get_Width() - 70, 0 ), 70, 20, "Next", cb_next )
    {
        this->callback( cb_quit );
        Attach( next_button );
    }
    void Wait_For_Button()
        // modified event loop:
        // handle all events (as per default), quit when button_pushed becomes true
        // this allows graphics without control inversion
    {
        Show();
        while( !button_pushed )
        {
            Wait();
            Draw();
        }
        button_pushed = false;
        Redraw();
    }

    GraphLib::Button next_button;
private:
    bool button_pushed;

    static void cb_next( GraphLib::Address, GraphLib::Address addr ) // callback for next_button
        //	{ reference_to<Simple_window>(addr).next(); }
    {
        static_cast<Simple_Window *>( addr )->Next();
    }

    static void cb_quit( Fl_Widget*, GraphLib::Address )
    {
        exit( 0 );
    }

    void Next()
    {
        button_pushed = true;
    }

};
