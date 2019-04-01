#pragma once

#include <iostream>
#include <fstream>

template<typename point_type>
class Point{
    static_assert(std::is_floating_point<point_type>::value ||
                  std::is_same<point_type, short>::value ||
                  std::is_same<point_type, int>::value ||
                  std::is_same<point_type, long>::value,
                  "unrecognized or unsupported type in the Point class");
public:
    Point() : m_x{}, m_y{} {}
    Point(point_type x, point_type y) : m_x{x}, m_y{y} {}

    void SetPointX(const point_type x)
    {
        m_x = x;
    }
    void SetPointY(const point_type y)
    {
        m_y = y;
    }
    point_type GetPointX() const
    {
        return m_x;
    }
    point_type GetPointY() const
    {
        return m_y;
    }

private:
    point_type m_x;
    point_type m_y;
};

// can use template for std::istream or with std::ifstream
template<typename T, typename point>
T& operator>>(T& in, Point<point>& p)
{
    static_assert(std::is_same<T, std::istream>::value ||
                  std::is_same<T, std::ifstream>::value,
                  "unrecognized or unsupported input stream type in Point class");
    in.exceptions(in.exceptions() | std::ios::badbit);
    point x{}, y{};
    in >> x >> y;
    if(in.fail()) return in;
    p.SetPointX(x);
    p.SetPointY(y);
    return in;
}

template<typename T, typename point>
T& operator<<(T& out, const Point<point>& p)
{
    static_assert(std::is_same<T, std::ostream>::value ||
                  std::is_same<T, std::ofstream>::value,
                  "unrecognized or unsupported output stream type in Point class");
    if(typeid(T) == typeid(std::ostream)){
        out << "(" << p.GetPointX() << "," << p.GetPointY() << ")";
    }
    else if(typeid(T) == typeid(std::ofstream)){
        out << p.GetPointX() << " " << p.GetPointY() << "\n";
    }
    return out;
}
