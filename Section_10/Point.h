#pragma once

#include <iostream>

class Point{
public:
    Point();
    Point(int x, int y);

    void SetPointX(const int x);
    void SetPointY(const int y);
    int GetPointX() const;
    int GetPointY() const;

private:
    int m_x;
    int m_y;
};

std::ostream& operator<<(std::ostream& os, const Point& p);
//std::istream& operator>>(std::istream& os, Point& p);
