#include "Window.hpp"
#include "GUI.hpp"

namespace GraphLib
{

    Window::Window( int width, int height, const std::string &title )
        : Fl_Window{ width, height, title.c_str() }, m_width{ width }, m_height{ height }
    {
        Init();
    }

    Window::Window( Point top_left, int width, int height, const std::string &title )
        : Fl_Window{ top_left.x, top_left.y, width, height, title.c_str() }, m_width{ width }, m_height{ height }
    {
        Init();
    }

    int Window::Get_Width() const
    {
        return m_width;
    }

    int Window::Get_Height() const
    {
        return m_height;
    }

    void Window::Resize( int new_width, int new_height )
    {
        m_width = new_width;
        m_height = new_height;
        size( new_width, new_height );
    }

    std::string Window::Get_Label() const
    {
        return std::string{ Fl_Window::label() };
    }

    void Window::Set_Label( const std::string &s )
    {
        Fl_Window::label( s.c_str() );
    }

    void Window::Attach( Shape &shape )
    {
        m_shapes.push_back( &shape );
        //		s.attached = this;
    }

    void Window::Attach( Widget &widget )
    {
        begin();				// FTLK: begin attaching new Fl_Wigets to this window
        widget.Attach( *this );	// let the Widget create its Fl_Wigits
        end();					// FTLK: stop attaching new Fl_Wigets to this window
    }

    void Window::Detach( Shape &shape )
    {
        auto itr = std::find( m_shapes.begin(), m_shapes.end(), &shape );
        m_shapes.erase( itr );
        //for( auto index{ m_shapes.size() }; 0 < index; --index )	// guess last attached will be first released
        //    if( m_shapes[index - 1] == &shape )
        //        m_shapes.erase( m_shapes.begin() + ( index - 1 ) ); //&shapes[i-1]);
    }

    void Window::Detach_Clear()
    {
        m_shapes.clear();
    }

    void Window::Detach( Widget &widget )
    {
        widget.Hide();
    }

    void Window::Put_On_Top( Shape &priority )  // todo this looks suspect
    {
        for( size_t index{}; index < m_shapes.size(); ++index )
        {
            if( &priority == m_shapes[index] )
            {
                for( ++index; index < m_shapes.size(); ++index )
                {
                    m_shapes.at( index - 1 ) = m_shapes[index];
                }
                m_shapes.at( m_shapes.size() - 1 ) = &priority;
                return;
            }
        }
    }

    void Window::Fullscreen()
    {
        Fl_Window::fullscreen();
    }

    void Window::Fullscreen_Off()
    {
        Fl_Window::fullscreen_off();
    }

    int Window::Fullscreen_Active() const
    {
        return Fl_Window::fullscreen_active();
    }

    void Window::Resize( int x, int y, int w, int h )
    {
        Fl_Window::resize( x, y, w, h );
    }

    void Window::Reposition( int x, int y )
    {
        Fl_Widget::position( x, y );
    }

    void Window::Draw()
    {
        for( const auto shape : m_shapes )
        {
            shape->Draw();
        }
    }

    void Window::Show()
    {
        Fl_Window::show();
    }

    void Window::Hide()
    {
        Fl_Window::hide();
    }

    int Window::Wait()
    {
        return Fl::wait();
    }

    void Window::Redraw()
    {
        Fl::redraw();
    }

    void Window::Init()
    {
        resizable( this );
        show();
    }

    int gui_main() { return Fl::run(); }

} // GraphLib
