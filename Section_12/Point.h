
#ifndef POINT_GUARD_H
#define POINT_GUARD_H

//typedef void (*Callback)(void*,void*);

namespace Graph_lib
{
	struct Point
	{
		int x, y;
		Point(int xx, int yy) : x{xx}, y{yy} { }
		Point() :x(0), y(0) { }

	//	Point& operator+=(Point d) { x+=d.x; y+=d.y; return *this; }
	};

	inline bool operator==(const Point &a, const Point &b) { return a.x == b.x && a.y == b.y; }

	inline bool operator!=(const Point &a, const Point &b) { return !(a == b); }
} //Graph_lib
#endif // POINT_GUARD_H