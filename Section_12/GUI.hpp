
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#pragma once

#include "Window.hpp"
#include "Graph.hpp"

#include <string>

namespace GraphLib
{
    using Address = void *;                         // Address is a synonym for void*
    using Callback = void( * )( Address, Address ); // FLTK's required function type for all callbacks

    template<class W>
    W &reference_to( Address pw )
        // treat an address as a reference to a W
    {
        return *static_cast<W *>( pw );
    }

    //------------------------------------------------------------------------------

    class Widget
    {
        // Widget is a handle to an Fl_widget - it is *not* an Fl_widget
        // We try to keep our interface classes at arm's length from FLTK
    public:
        Widget( Point xy, int w, int h, const std::string &s, Callback cb )
            : location{ xy }, width{ w }, height{ h }, label{ s }, widget_callback{ cb }, own{ nullptr }, pwidget{ nullptr }
        {}

        virtual void Move( int dx, int dy )
        {
            Hide();
            pwidget->position( location.x += dx, location.y += dy );
            Show();
        }
        virtual void Hide() { pwidget->hide(); }
        virtual void Show() { pwidget->show(); }
        virtual void Attach( GraphLib::Window & ) = 0;

        Point location;
        int width;
        int height;
        std::string label;
        Callback widget_callback;

        virtual ~Widget() {}

        //Widget &operator=( const Widget & ) = delete;
        //Widget &operator=( const Widget && ) = delete;
        //Widget( const Widget & ) = delete;
        //Widget( const Widget && ) = delete;

    protected:
        Window *own;                        // every Widget belongs to a Window
        std::unique_ptr<Fl_Widget> pwidget; // connection to the FLTK Widget
    };

    //------------------------------------------------------------------------------

    struct Button : public Widget
    {
        Button( Point xy, int w, int h, const std::string &label, Callback cb )
            : Widget( xy, w, h, label, cb )
        {}

        void Attach( Window &win ) override;
    };

    //------------------------------------------------------------------------------

    struct In_Box : Widget
    {
        In_Box( Point xy, int w, int h, const std::string &s )
            : Widget( xy, w, h, s, nullptr )
        {}
        int get_int();
        std::string get_string();

        void Attach( Window &win ) override;
    };

    //------------------------------------------------------------------------------

    struct Out_Box : Widget
    {
        Out_Box( Point xy, int w, int h, const std::string &s )
            : Widget( xy, w, h, s, 0 )
        {}
        void put( int );
        void put( const std::string & );

        void Attach( Window &win ) override;
    };

    //------------------------------------------------------------------------------

    struct Menu : Widget
    {
        enum class Kind { horizontal, vertical };

        Menu( Point xy, int w, int h, Kind k, const std::string &label )
            : Widget( xy, w, h, label, nullptr ), kind( k ), offset( 0 )
        {}

        Vector_Reference<Button> selection;
        Kind kind;
        int offset;
        int Attach( Button &b );      // Menu does not delete &b
        int Attach( Button *p );      // Menu deletes p

        void Show()                 // show all buttons
        {
            for( unsigned int i{}; i < selection.Size(); ++i )
            {
                selection[i].Show();
            }
        }
        void Hide()                 // hide all buttons
        {
            for( unsigned int i{}; i < selection.Size(); ++i )
            {
                selection[i].Hide();
            }
        }
        void Move( int dx, int dy )   // move all buttons
        {
            for( unsigned int i{}; i < selection.Size(); ++i )
            {
                selection[i].Move( dx, dy );
            }
        }

        void Attach( Window &win )    // attach all buttons
        {
            for( int i{}; i < selection.Size(); ++i )
            {
                win.Attach( selection[i] );
            }
            own = &win;
        }
    };

} // of namespace Graph_lib
