
#pragma once

#include "fltk.hpp"
#include "Point.hpp"
#include "utility.hpp"
#include <string>
#include <vector>

namespace GraphLib
{
    // defense against ill-behaved Linux macros:
#undef major
#undef minor

    struct Color
    {
        enum class Color_Type : unsigned int
        {
            red = FL_RED,
            blue = FL_BLUE,
            green = FL_GREEN,
            yellow = FL_YELLOW,
            white = FL_WHITE,
            black = FL_BLACK,
            magenta = FL_MAGENTA,
            cyan = FL_CYAN,
            dark_red = FL_DARK_RED,
            dark_green = FL_DARK_GREEN,
            dark_yellow = FL_DARK_YELLOW,
            dark_blue = FL_DARK_BLUE,
            dark_magenta = FL_DARK_MAGENTA,
            dark_cyan = FL_DARK_CYAN
        };

        enum class Transparency : unsigned char
        {
            invisible = 0,
            visible = 255
        };

        Color( Color_Type c )
            : color{ Fl_Color( Fl_Color( static_cast<unsigned int>( c ) ) ) }, transparency{ Transparency::visible }
        {}
        Color( Color_Type c, Transparency t )
            : color{ Fl_Color( static_cast<unsigned int>( c ) ) }, transparency{ t }
        {}
        Color( int c )
            : color{ Fl_Color( static_cast<unsigned int>( c ) ) }, transparency( Transparency::visible )
        {}
        Color( Transparency t )
            : color{ static_cast<Color::Color_Type>( Fl_Color() ) }, transparency{ t }
        {}

        int As_Int() const { return static_cast<int>( color ); }
        Transparency Get_Transparency() const { return transparency; }
        void Set_Transparency( Transparency t ) { transparency = t; }
    private:
        Transparency transparency;	// 0 or 255 for now
        Color_Type color;
    };

    struct Line_Style
    {
        enum class Line_Style_Type
        {
            solid = FL_SOLID,			// -------
            dash = FL_DASH,				// - - - -
            dot = FL_DOT,				// ....... 
            dashdot = FL_DASHDOT,		// - . - . 
            dashdotdot = FL_DASHDOTDOT,	// -..-..
        };

        Line_Style( Line_Style_Type lst )
            : style{ lst }, thickness{ 0 }
        {}
        Line_Style( Line_Style_Type lst, int w )
            : style{ lst }, thickness{ w }
        {}
        Line_Style( int ls )
            : style{ static_cast<Line_Style::Line_Style_Type>( ls ) }, thickness{ 0 }
        {}

        int Get_Width() const { return thickness; }
        Line_Style_Type Get_Style() const { return style; }
    private:
        Line_Style_Type style;
        int thickness;
    };

    class Font
    {
    public:
        enum class Font_Type
        {
            helvetica = FL_HELVETICA,
            helvetica_bold = FL_HELVETICA_BOLD,
            helvetica_italic = FL_HELVETICA_ITALIC,
            helvetica_bold_italic = FL_HELVETICA_BOLD_ITALIC,
            courier = FL_COURIER,
            courier_bold = FL_COURIER_BOLD,
            courier_italic = FL_COURIER_ITALIC,
            courier_bold_italic = FL_COURIER_BOLD_ITALIC,
            times = FL_TIMES,
            times_bold = FL_TIMES_BOLD,
            times_italic = FL_TIMES_ITALIC,
            times_bold_italic = FL_TIMES_BOLD_ITALIC,
            symbol = FL_SYMBOL,
            screen = FL_SCREEN,
            screen_bold = FL_SCREEN_BOLD,
            zapf_dingbats = FL_ZAPF_DINGBATS
        };

        Font( Font_Type f )
            : font{ f }
        {}
        Font( int f )
            : font{ static_cast<Font_Type>( f ) }
        {}

        int As_Int() const { return static_cast<int>( font ); }
    private:
        Font_Type font;
    };

    template<class T> class Vector_Reference
    {
        std::vector<T *> v;
        std::vector<T *> owned;
    public:
        Vector_Reference() {}

        Vector_Reference( T *a, T *b = nullptr, T *c = nullptr, T *d = nullptr )
        {
            if( a ) push_back( a );
            if( b ) push_back( b );
            if( c ) push_back( c );
            if( d ) push_back( d );
        }

        ~Vector_Reference()
        {
            for( T *i : owned ) { delete i; }
        }

        void push_back( T &s ) { v.push_back( &s ); }
        void push_back( T *p )
        {
            v.push_back( p );
            owned.push_back( p );
        }

        // ???void erase(???)

        T &operator[]( int i ) { return *v[i]; }
        const T &operator[]( int i ) const { return *v[i]; }
        decltype( v.size() ) Size() const { return v.size(); }
    };

    using Fct = double( * )( double );

    class Shape
    {	// deals with color and style, and holds sequence of lines
    public:
        Shape() {}
        Shape( std::initializer_list<Point> lst );  // add() the Points to this Shape

        //	Shape() : lcolor(fl_color()),
        //		ls(0),
        //		fcolor(Color::invisible) { }

        void Add( Point p ) { points.push_back( p ); }
        void Set_Point( int i, Point p ) { points.at( i ) = p; }
    public:
        void Draw() const;    					// deal with color and draw_lines
    protected:
        virtual void Draw_Lines() const;    	// simply draw the appropriate lines
    public:
        virtual void Move( int dx, int dy );	// move the shape +=dx and +=dy

        void Set_Color( Color lc ) { line_color = lc; }
        Color Get_Color() const { return line_color; }

        void Set_Style( Line_Style lst ) { line_style = lst; }
        Line_Style Get_Style() const { return line_style; }

        void Set_Fill_Color( Color fc ) { fill_color = fc; }
        Color Get_Fill_Color() const { return fill_color; }

        Point Get_Point( int i ) const { return points.at( i ); }
        int Number_Of_Points() const { return int( points.size() ); }

        virtual ~Shape() {}
        /*
        struct Window* attached;
        Shape(const Shape& a)
            :attached(a.attached), points(a.points), line_color(a.line_color), ls(a.ls)
        {
            if (a.attached)error("attempt to copy attached shape");
        }
        */

        /*Shape( const Shape & ) = delete;
        Shape( const Shape && ) = delete;
        Shape &operator=( const Shape & ) = delete;
        Shape &operator=( const Shape && ) = delete;*/
    private:
        std::vector<Point> points;	// not used by all shapes
        Color line_color{ static_cast<Color::Color_Type>( fl_color() ) };
        Line_Style line_style{ Line_Style::Line_Style_Type::solid };
        Color fill_color{ Color::Transparency::invisible };
    };

    struct Function : Shape
    {
        // the function parameters are not stored
        Function( Fct f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25 );
        //Function(Point orig, Fct f, double r1, double r2, int count, double xscale = 1, double yscale = 1);	
    };

    struct Fill
    {
        Fill()
            : no_fill{ true }, fill_color{ static_cast<Color::Color_Type>( 0 ) }
        {}
        Fill( Color c )
            : no_fill{ false }, fill_color{ c }
        {}

        void Set_Fill_Color( Color fc ) { fill_color = fc; }
        Color Get_Fill_Color() const { return fill_color; }
    protected:
        bool no_fill;
        Color fill_color;
    };

    struct Line : Shape
    {
        Line( Point p1, Point p2 )
        {
            Add( p1 );
            Add( p2 );
        }
    };

    struct Rectangle : Shape
    {

        Rectangle( Point xy, int w, int h )
            : width{ w }, height{ h }
        {
            if( height <= 0 || width <= 0 )
            {
                throw std::runtime_error( std::format( "Bad rectangle: non-positive side, width {}, height {}.", width, height ) );
            }
            Add( xy );
        }

        Rectangle( Point x, Point y )
            : width{ y.x - x.x }, height{ y.y - x.y }
        {
            if( height <= 0 || width <= 0 )
            {
                throw std::runtime_error( std::format( "Bad rectangle: first point is not top left, width {}, height {}.",
                                          width, height ) );
            }
            Add( x );
        }
        void Draw_Lines() const;

        //	void set_fill_color(Color col) { fcolor = col; }
        //	Color fill_color() { return fcolor; }

        int Get_Height() const { return height; }
        int Get_Width() const { return width; }
    private:
        int height;			// height
        int width;			// width
        //	Color fill_color;	// fill color; 0 means "no fill"
    };

    bool Intersect( Point p1, Point p2, Point p3, Point p4 );

    struct Open_Polyline : Shape
    {	// open sequence of lines
        using Shape::Shape; // ??
        void Add( Point p ) { Shape::Add( p ); }
        void Draw_Lines() const;
    };

    struct Closed_Polyline : Open_Polyline
    {	// closed sequence of lines
        using Open_Polyline::Open_Polyline; // ??
        void Draw_Lines() const;

        //	void add(Point p) { Shape::add(p); }
    };

    struct Polygon : Closed_Polyline
    {	// closed sequence of non-intersecting lines
        using Closed_Polyline::Closed_Polyline; // ??
        void Add( Point p );
        void Draw_Lines() const;
    };

    struct Lines : Shape    // independent lines
    {
        Lines() {}
        Lines( std::initializer_list<Point> lst )
            : Shape{ lst }
        {
            if( lst.size() % 2 )
            {
                throw std::runtime_error( "odd number of points for Lines" );
            }
        }
        void Draw_Lines() const;
        void Add( Point p1, Point p2 )
        {
            Shape::Add( p1 );
            Shape::Add( p2 );
        }
    };

    struct Text : Shape
    {
        // the point is the bottom left of the first letter
        Text( Point x, const std::string &s )
            : label{ s }
        {
            Add( x );
        }

        void Draw_Lines() const;
        void Set_Labels( const std::string &s ) { label = s; }
        std::string Get_Label() const { return label; }
        void Set_Font( Font f ) { font = f; }
        Font Get_Font() const { return Font( font ); }
        void Set_Font_Size( int s ) { font_size = s; }
        int Get_Font_Size() const { return font_size; }
    private:
        std::string label;
        Font font{ fl_font() };
        int font_size{ ( 14 < fl_size() ) ? fl_size() : 14 };	// at least 14 point
    };

    struct Axis : Shape
    {
        // representation left public
        enum class Orientation { x, y, z };
        Axis( Orientation d, Point xy, int length, int nummber_of_notches = 0, std::string label = "" );

        void Draw_Lines() const;
        void Move( int dx, int dy );
        void Set_Color( Color c );

        Text label;
        Lines notches;
        //	Orientation origin;
        //	int notches;
    };

    struct Circle : Shape
    {
        Circle( Point p, int r )	// center and radius
            : radius{ r }
        {
            Add( Point{ p.x - radius, p.y - radius } );
        }

        void Draw_Lines() const;
        Point Get_Center() const
        {
            return Point{ Get_Point( 0 ).x + radius, Get_Point( 0 ).y + radius };
        }
        void Set_Radius( int r ) { radius = r; }
        int Get_Radius() const { return radius; }
    private:
        int radius;
    };


    struct Ellipse : Shape
    {
        Ellipse( Point p, int w, int h )	// center, min, and max distance from center
            : width{ w }, height{ h }
        {
            Add( Point{ p.x - w, p.y - h } );
        }

        void Draw_Lines() const;

        Point Get_Center() const
        {
            return Point{ Get_Point( 0 ).x + width, Get_Point( 0 ).y + height };
        }
        Point Get_Focus1() const
        {
            return Point{ Get_Center().x + int( std::sqrt( narrow_cast<double, int>( width * width - height * height ) ) ),
                Get_Center().y };
        }
        Point Get_Focus2() const
        {
            return Point{ Get_Center().x - int( std::sqrt( narrow_cast<double, int>( width * width - height * height ) ) ),
            Get_Center().y };
        }

        void Set_Major( int w ) { width = w; }
        int Get_Major() const { return width; }
        void Set_Minor( int h ) { height = h; }
        int Get_Minor() const { return height; }
    private:
        int width;
        int height;
    };
    /*
    struct Mark : Text {
        static const int dw = 4;
        static const int dh = 4;
        Mark(Point xy, char c) : Text(Point(xy.x-dw, xy.y+dh),string(1,c)) {}
    };
    */

    struct Marked_polyline : Open_Polyline
    {
        Marked_polyline( const std::string &m )
            : mark( m )
        {}
        void Draw_Lines() const;
    private:
        std::string mark;
    };

    struct Marks : Marked_polyline
    {
        Marks( const std::string &m )
            : Marked_polyline( m )
        {
            Set_Color( Color{ Color::Transparency::invisible } );
        }
    };

    struct Mark : Marks
    {
        Mark( Point xy, char c )
            : Marks( std::string( 1, c ) )
        {
            Add( xy );
        }
    };

    /*

    struct Marks : Shape {
        Marks(char m) : mark(string(1,m)) { }
        void add(Point p) { Shape::add(p); }
        void draw_lines() const;
    private:
        string mark;
    };
    */

    struct Bad_image : Fl_Image
    {
        Bad_image( int h, int w )
            : Fl_Image( h, w, 0 )
        {}
        void Draw( int x, int y, int, int, int, int ) { draw_empty( x, y ); }
    };

    struct Suffix
    {
        enum class Encoding { none, jpg, gif, bmp };
    };

    Suffix::Encoding Get_Encoding( const std::string &s );

    struct Image : Shape
    {
        Image( Point xy, std::string s, Suffix::Encoding e = Suffix::Encoding::none );
        ~Image() { delete p; }
        void Draw_Lines() const;
        void Set_Mask( Point xy, int ww, int hh )
        {
            w = ww;
            h = hh;
            cx = xy.x;
            cy = xy.y;
        }
        void Move( int dx, int dy )
        {
            Shape::Move( dx, dy );
            p->draw( Get_Point( 0 ).x, Get_Point( 0 ).y );
        }
    private:
        int w, h, cx, cy; // define "masking box" within image relative to position (cx,cy)
        Fl_Image *p;
        Text fn;
    };

} // GraphLib
