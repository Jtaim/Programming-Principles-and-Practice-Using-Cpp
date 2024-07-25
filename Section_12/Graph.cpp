#include "Graph.hpp"
#include <fstream>
#include <map>

namespace GraphLib
{
    void Shape::Draw_Lines() const
    {
        if( Get_Color().Get_Transparency() == Color::Transparency::visible && 1 < points.size() )	// draw sole pixel?
        {
            for( size_t index{ 1 }; index < points.size(); ++index )
            {
                fl_line( points[index - 1].x, points[index - 1].y, points[index].x, points[index].y );
            }
        }
    }

    Shape::Shape( std::initializer_list<Point> lst )
    {
        for( const auto &p : lst )
        {
            Add( p );
        }
    }

    void Shape::Draw() const
    {
        Fl_Color old_color{ fl_color() };
        // there is no good portable way of retrieving the current style
        fl_color( line_color.As_Int() );
        fl_line_style( static_cast<int>( line_style.Get_Style() ), line_style.Get_Width() );
        Draw_Lines();
        fl_color( old_color );	// reset color (to previous) and style (to default)
        fl_line_style( static_cast<int>( Line_Style::Line_Style_Type::solid ) );
    }

    // does two lines (p1,p2) and (p3,p4) intersect?
    // if false return the distance of the intersect point as distances from p1
    std::pair<double, double> line_intersect( Point p1, Point p2, Point p3, Point p4, bool &parallel )
    {
        auto x1{ narrow_cast<double, decltype( Point::x )>( p1.x ) };
        auto x2{ narrow_cast<double, decltype( Point::x )>( p2.x ) };
        auto x3{ narrow_cast<double, decltype( Point::x )>( p3.x ) };
        auto x4{ narrow_cast<double, decltype( Point::x )>( p4.x ) };
        auto y1{ narrow_cast<double, decltype( Point::y )>( p1.y ) };
        auto y2{ narrow_cast<double, decltype( Point::y )>( p2.y ) };
        auto y3{ narrow_cast<double, decltype( Point::y )>( p3.y ) };
        auto y4{ narrow_cast<double, decltype( Point::y )>( p4.y ) };

        auto denom{ ( y4 - y3 ) * ( x2 - x1 ) - ( x4 - x3 ) * ( y2 - y1 ) };
        if( denom == 0 )    // TODO fix comparing to a floating point
        {
            parallel = true;
            return std::pair<double, double>{ 0.0, 0.0 };
        }
        parallel = false;
        return std::pair<double, double>
        { ( ( x4 - x3 ) *( y1 - y3 ) - ( y4 - y3 ) * ( x1 - x3 ) ) / denom,
            ( ( x2 - x1 ) *( y1 - y3 ) - ( y2 - y1 ) * ( x1 - x3 ) ) / denom };
    }

    //intersection between two line segments
    //Returns true if the two segments intersect,
    //in which case intersection is set to the point of intersection
    bool line_segment_intersect( Point p1, Point p2, Point p3, Point p4, Point &intersection )
    {
        bool parallel;
        auto u{ line_intersect( p1, p2, p3, p4, parallel ) };
        if( parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1 ) // TODO fix comparing to a floating point
        {
            return false;
        }
        intersection.x = static_cast<int>( p1.x + u.first * narrow_cast<double, decltype( Point::x )>( p2.x - p1.x ) );
        intersection.y = static_cast<int>( p1.y + u.first * narrow_cast<double, decltype( Point::y )>( p2.y - p1.y ) );
        return true;
    }

    void Polygon::Add( Point p )
    {
        auto np{ Number_Of_Points() };

        if( 1 < np )
        {	// check that the new line isn't parallel to the previous one
            if( p == Get_Point( np - 1 ) )
            {
                throw std::runtime_error( "polygon point equal to previous point" );
            }
            bool parallel{};
            line_intersect( Get_Point( np - 1 ), p, Get_Point( np - 2 ), Get_Point( np - 1 ), parallel );
            if( parallel )
            {
                throw std::runtime_error( "two polygon points lie in a straight line" );
            }
        }

        for( int i{ 1 }; i < np - 1; ++i )
        {	// check that new segment doesn't intersect and old point
            Point ignore( 0, 0 );
            if( line_segment_intersect( Get_Point( np - 1 ), p, Get_Point( i - 1 ), Get_Point( i ), ignore ) )
            {
                throw std::runtime_error( "intersect in polygon" );
            }
        }

        Closed_Polyline::Add( p );
    }

    void Polygon::Draw_Lines() const
    {
        if( Number_Of_Points() < 3 )
        {
            throw std::runtime_error( "less than 3 points in a Polygon" );
        }
        Closed_Polyline::Draw_Lines();
    }

    void Open_Polyline::Draw_Lines() const
    {
        if( Get_Fill_Color().Get_Transparency() == Color::Transparency::visible )
        {
            fl_color( Get_Fill_Color().As_Int() );
            fl_begin_complex_polygon();
            for( int i{}; i < Number_Of_Points(); ++i )
            {
                fl_vertex( Get_Point( i ).x, Get_Point( i ).y );
            }
            fl_end_complex_polygon();
            fl_color( Get_Color().As_Int() );	// reset color
        }

        if( Get_Color().Get_Transparency() == Color::Transparency::visible )
        {
            Shape::Draw_Lines();
        }
    }

    void Closed_Polyline::Draw_Lines() const
    {
        Open_Polyline::Draw_Lines();

        if( Get_Color().Get_Transparency() == Color::Transparency::visible )	// draw closing line:
        {
            fl_line( Get_Point( Number_Of_Points() - 1 ).x, Get_Point( Number_Of_Points() - 1 ).y,
                     Get_Point( 0 ).x, Get_Point( 0 ).y );
        }
    }

    void Shape::Move( int dx, int dy )
    {
        for( size_t index{}; index < points.size(); ++index )
        {
            points[index].x += dx;
            points[index].y += dy;
        }
    }

    void Lines::Draw_Lines() const
    {
        //	if (number_of_points()%2==1) error("odd number of points in set of lines");
        if( Get_Color().Get_Transparency() == Color::Transparency::visible )
        {
            for( int i{ 1 }; i < Number_Of_Points(); i += 2 )
            {
                fl_line( Get_Point( i - 1 ).x, Get_Point( i - 1 ).y,
                         Get_Point( i ).x, Get_Point( i ).y );
            }
        }
    }

    void Text::Draw_Lines() const
    {
        auto ofnt{ fl_font() };
        auto osz{ fl_size() };
        fl_font( font.As_Int(), font_size );
        fl_draw( label.c_str(), Get_Point( 0 ).x, Get_Point( 0 ).y );
        fl_font( ofnt, osz );
    }

    Function::Function( Fct funct, double r1, double r2, Point xy, int count, double xscale, double yscale )
        // graph f(x) for x in [r1:r2) using count line segments with (0,0) displayed at xy
        // x coordinates are scaled by xscale and y coordinates scaled by yscale
    {
        if( r2 - r1 <= 0 )  // TODO fix float compare
        {
            throw std::runtime_error( "bad graphing range" );
        }
        if( count <= 0 )
        {
            throw std::runtime_error( "non-positive graphing count" );
        }
        auto dist{ ( r2 - r1 ) / count };
        auto r{ r1 };
        for( int i{}; i < count; ++i )
        {
            Add( Point( xy.x + static_cast<int>( r * xscale ), xy.y - static_cast<int>( funct( r ) * yscale ) ) );
            r += dist;
        }
    }

    void Rectangle::Draw_Lines() const
    {
        if( Get_Fill_Color().Get_Transparency() == Color::Transparency::visible )
        {	// fill
            fl_color( Get_Fill_Color().As_Int() );
            fl_rectf( Get_Point( 0 ).x, Get_Point( 0 ).y, width, height );
            fl_color( Get_Color().As_Int() );	// reset color
        }

        if( Get_Color().Get_Transparency() == Color::Transparency::visible )
        {	// edge on top of fill
            fl_color( Get_Color().As_Int() );
            fl_rect( Get_Point( 0 ).x, Get_Point( 0 ).y, width, height );
        }
    }

    Axis::Axis( Orientation d, Point xy, int length, int n, std::string lab )
        :label{ Point( 0, 0 ), lab }
    {
        if( length < 0 )
        {
            throw std::runtime_error( "bad axis length" );
        }
        switch( d )
        {
            case Axis::Orientation::x:
            {
                Shape::Add( xy );	// axis line
                Shape::Add( Point( xy.x + length, xy.y ) );	// axis line
                if( 1 < n )
                {
                    int dist = length / n;  // will truncate
                    int x = xy.x + dist;
                    for( int i = 0; i < n; ++i )
                    {
                        notches.Add( Point( x, xy.y ), Point( x, xy.y - 5 ) );
                        x += dist;
                    }
                }
                // label under the line
                label.Move( length / 3, xy.y + 20 );
                break;
            }
            case Axis::Orientation::y:
            {
                Shape::Add( xy );	// a y-axis goes up
                Shape::Add( Point( xy.x, xy.y - length ) );
                if( 1 < n )
                {
                    int dist = length / n;
                    int y = xy.y - dist;
                    for( int i = 0; i < n; ++i )
                    {
                        notches.Add( Point( xy.x, y ), Point( xy.x + 5, y ) );
                        y -= dist;
                    }
                }
                // label at top
                label.Move( xy.x - 10, xy.y - length - 10 );
                break;
            }
            case Axis::Orientation::z:
                throw std::runtime_error( "z axis not implemented" );
        }
    }

    void Axis::Draw_Lines() const
    {
        Shape::Draw_Lines();	// the line
        notches.Draw();	// the notches may have a different color from the line
        label.Draw();	// the label may have a different color from the line
    }

    void Axis::Set_Color( Color c )
    {
        Shape::Set_Color( c );
        notches.Set_Color( c );
        label.Set_Color( c );
    }

    void Axis::Move( int dx, int dy )
    {
        Shape::Move( dx, dy );
        notches.Move( dx, dy );
        label.Move( dx, dy );
    }

    void Circle::Draw_Lines() const
    {
        if( Get_Fill_Color().Get_Transparency() == Color::Transparency::visible )
        {	// fill
            fl_color( Get_Fill_Color().As_Int() );
            fl_pie( Get_Point( 0 ).x, Get_Point( 0 ).y, radius + radius - 1, radius + radius - 1, 0, 360 );
            fl_color( Get_Color().As_Int() );	// reset color
        }

        if( Get_Color().Get_Transparency() == Color::Transparency::visible )
        {
            fl_color( Get_Color().As_Int() );
            fl_arc( Get_Point( 0 ).x, Get_Point( 0 ).y, radius + radius, radius + radius, 0, 360 );
        }
    }

    void Ellipse::Draw_Lines() const
    {
        if( Get_Fill_Color().Get_Transparency() == Color::Transparency::visible )
        {	// fill
            fl_color( Get_Fill_Color().As_Int() );
            fl_pie( Get_Point( 0 ).x, Get_Point( 0 ).y, width + width - 1, height + height - 1, 0, 360 );
            fl_color( Get_Color().As_Int() );	// reset color
        }

        if( Get_Color().Get_Transparency() == Color::Transparency::visible )
        {
            fl_color( Get_Color().As_Int() );
            fl_arc( Get_Point( 0 ).x, Get_Point( 0 ).y, width + width, height + height, 0, 360 );
        }
    }

    void draw_mark( Point xy, char c )
    {
        static const int dx = 4;
        static const int dy = 4;
        std::string m( 1, c );
        fl_draw( m.c_str(), xy.x - dx, xy.y + dy );
    }

    void Marked_polyline::Draw_Lines() const
    {
        Open_Polyline::Draw_Lines();
        for( int i = 0; i < Number_Of_Points(); ++i )
            draw_mark( Get_Point( i ), mark[i % mark.size()] );
    }
    /*
    void Marks::draw_lines() const
    {
        for (int i=0; i<number_of_points(); ++i)
            fl_draw(mark.c_str(),point(i).x-4,point(i).y+4);
    }
    */

    std::map<std::string, Suffix::Encoding> suffix_map;

    int init_suffix_map()
    {
        suffix_map["jpg"] = Suffix::Encoding::jpg;
        suffix_map["JPG"] = Suffix::Encoding::jpg;
        suffix_map["jpeg"] = Suffix::Encoding::jpg;
        suffix_map["JPEG"] = Suffix::Encoding::jpg;
        suffix_map["gif"] = Suffix::Encoding::gif;
        suffix_map["GIF"] = Suffix::Encoding::gif;
        suffix_map["bmp"] = Suffix::Encoding::bmp;
        suffix_map["BMP"] = Suffix::Encoding::bmp;
        return 0;
    }

    Suffix::Encoding Get_Encoding( const std::string &s )
        // try to deduce type from file name using a lookup table
    {
        static int x = init_suffix_map();

        std::string::const_iterator p = find( s.begin(), s.end(), '.' );
        if( p == s.end() ) return Suffix::Encoding::none;	// no suffix

        std::string suf( p + 1, s.end() );
        return suffix_map[suf];
    }

    bool can_open( const std::string &s )
        // check if a file named s exists and can be opened for reading
    {
        std::ifstream ff{ s.c_str() };
        return ff.is_open();
    }

    // somewhat over elaborate constructor
    // because errors related to image files can be such a pain to debug
    Image::Image( Point xy, std::string s, Suffix::Encoding e )
        : w{}, h{}, cx{}, cy{}, fn( xy, "" )
    {
        Add( xy );
        if( !can_open( s ) )
        {
            fn.Set_Labels( "cannot open \"" + s + '\"' );
            p = new Bad_image( 30, 20 );	// the "error image"
            return;
        }

        if( e == Suffix::Encoding::none )
        {
            e = Get_Encoding( s );
        }

        switch( e )
        {
            case Suffix::Encoding::jpg:
                p = new Fl_JPEG_Image( s.c_str() );
                break;
            case Suffix::Encoding::gif:
                p = new Fl_GIF_Image( s.c_str() );
                break;
                //case Suffix::Encoding::bmp:
                //    p = std::make_unique<Fl_Image>( Fl_BMP_Image( s.c_str() ) );
                //    break;
            default:	// Unsupported image encoding
                fn.Set_Labels( "unsupported file type \"" + s + '\"' );
                p = new Bad_image( 30, 20 );	// the "error image"
                break;
        }
    }

    void Image::Draw_Lines() const
    {
        if( fn.Get_Label() != "" )
        {
            fn.Draw_Lines();
        }
        if( w && h )
        {
            p->draw( Get_Point( 0 ).x, Get_Point( 0 ).y, w, h, cx, cy );
        }
        else
        {
            p->draw( Get_Point( 0 ).x, Get_Point( 0 ).y );
        }
    }

} // GraphLib
