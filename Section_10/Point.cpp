#include "Point.h"

Point::Point()
    : m_x{0}, m_y{0}
{}

Point::Point(int x, int y)
    : m_x{x}, m_y{y}
{}

void Point::SetPointX(const int x)
{
    m_x = x;
}

void Point::SetPointY(const int y)
{
    m_y = y;
}

int Point::GetPointX() const
{
    return m_x;
}

int Point::GetPointY() const
{
    return m_y;
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    std::cout << "(" << p.GetPointX() << "," << p.GetPointY() << ")";
    return os;
}
