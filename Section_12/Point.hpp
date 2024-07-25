#pragma once

//using Callback = void( * )( void *, void * );

namespace GraphLib
{
    struct Point
    {
        int x, y;
        Point() :x{}, y{} {}
        Point( int xx, int yy ) : x{ xx }, y{ yy } {}
    };

    inline bool operator==( const Point &a, const Point &b ) { return a.x == b.x && a.y == b.y; }
    inline bool operator!=( const Point &a, const Point &b ) { return !( a == b ); }

}       //namespace GraphLib
