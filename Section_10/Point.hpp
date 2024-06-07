#pragma once

#include <iostream>
#include <fstream>

template<typename point_type>
class Point
{
    static_assert( std::is_floating_point<point_type>::value ||
                   std::is_same<point_type, short>::value ||
                   std::is_same<point_type, int>::value ||
                   std::is_same<point_type, long>::value,
                   "unrecognized or unsupported type in the Point class" );
public:
    Point() : m_x{}, m_y{} {};
    Point( point_type x, point_type y ) : m_x{ x }, m_y{ y } {}

    void SetPointX( const point_type x ) { m_x = x; }
    void SetPointY( const point_type y ) { m_y = y; }
    point_type GetPointX() const { return m_x; }
    point_type GetPointY() const { return m_y; }

private:
    point_type m_x;
    point_type m_y;
};

// template for std::istream or with std::ifstream overloads
// -----------------------------------------------------------------------------------
template<typename T, typename point_type>
T &operator>>( T &in, Point<point_type> &p )
{
    static_assert( std::is_same<T, std::istream>::value ||
                   std::is_same<T, std::ifstream>::value ||
                   std::is_same<T, std::istringstream>::value,
                   "unrecognized or unsupported input stream type in Point class" );
    in.exceptions( in.exceptions() | std::ios::badbit );
    point_type x{}, y{};
    in >> x;
    if( in.fail() )
    {
        return in;
    }
    while( !( in >> y ) )
    {
        in.clear();
        char c{};
        if( !( in >> c ) || c != ',' )
        {
            in.unget();
            in.clear( std::ios::failbit );
            return in;
        }
    }
    p.SetPointX( x );
    p.SetPointY( y );
    return in;
}

// template for std::ostream or with std::ofstream overloads
// ostream has some extra display candy
// ofstream store point with new line indicating a new point
// -----------------------------------------------------------------------------------
template<typename T, typename point_type>
T &operator<<( T &out, const Point<point_type> &p )
{
    static_assert( std::is_same<T, std::ostream>::value ||
                   std::is_same<T, std::ofstream>::value ||
                   std::is_same<T, std::ostringstream>::value,
                   "unrecognized or unsupported output stream type in Point class" );
    out.exceptions( out.exceptions() | std::ios::badbit );
    if constexpr( typeid( T ) == typeid( std::ostream ) )
    {
        out << "(" << p.GetPointX() << ", " << p.GetPointY() << ")";
    }
    if constexpr( typeid( T ) == typeid( std::ofstream ) || typeid( T ) == typeid( std::ostringstream ) )
    {
        out << p.GetPointX() << ", " << p.GetPointY() << "\n";
    }
    return out;
}

// template for relational operator overloads
// -----------------------------------------------------------------------------------
template<typename point_type>
bool operator==( const Point<point_type> &lhs, const Point<point_type> &rhs )
{
    return ( lhs.GetPointX() == rhs.GetPointX() && lhs.GetPointY() == rhs.GetPointY() );
}

template<typename point_type>
bool operator>( const Point<point_type> &lhs, const Point<point_type> &rhs )
{
    return ( lhs.GetPointX() > rhs.GetPointX() && lhs.GetPointY() > rhs.GetPointY() );
}

template<typename point_type>
bool operator<( const Point<point_type> &lhs, const Point<point_type> &rhs )
{
    return ( lhs.GetPointX() < rhs.GetPointX() && lhs.GetPointY() < rhs.GetPointY() );
}

template<typename point_type>
bool operator!=( const Point<point_type> &lhs, const Point<point_type> &rhs )
{
    return !( lhs == rhs );
}

template<typename point_type>
bool operator>=( const Point<point_type> &lhs, const Point<point_type> &rhs )
{
    return !( lhs == rhs || lhs > rhs );
}

template<typename point_type>
bool operator<=( const Point<point_type> &lhs, const Point<point_type> &rhs )
{
    return !( lhs == rhs || lhs < rhs );
}
