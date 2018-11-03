//written by Jtaim
//date 6 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
section 5 exercise 7.
build upon section 4 exercise 18.
Write a program to solve quadratic equations(ax^2+bx+c=0).
x = (-b +/- sqrt(b^2-4ac))/2a
Check that b^2-4ac is not less than 0.
Write a function that print out the roots of a quadratic equation, given a,b,c.
If no real roots print out a message.
*/

#include "section5.h"

void quadratic(const double a, const double b, const double c)
{
    using std::cout;
    if (a == 0) {
        error("a = 0; so can not derive any roots\n");
    }
    else if (c == 0) {
        cout << "x = 0\n";
        cout << "x = " << -1.0 * b / a << '\n';
    }
    else {
        auto sq = b * b - 4.0 * a*c;
        if (sq >= 0) {
            cout << "x = " << (-1.0 * b + sqrt(sq)) / (2.0 * a) << '\n';
            cout << "x = " << (-1.0 * b - sqrt(sq)) / (2.0 * a) << '\n';
        }
        else {
            cout << "x = (" << -1.0 * b << " +i" << sqrt(fabs(sq)) << ")/" << (2.0 * a) << '\n';
            cout << "x = (" << -1.0 * b << " -i" << sqrt(fabs(sq)) << ")/" << (2.0 * a) << '\n';
        }
    }
}

int main()
try
{
    using std::cout;
    using std::cin;

    cout << "Enter the a, b and c variables to solve the quadratic equation:\n";
    double a{ 0.0 };
    double b{ 1.0 };
    double c{ 0.0 };
    while (!(cin >> a >> b >> c)) {
        cin.clear();
        cin.ignore(UINT8_MAX, '\n');
        cout << "non-numeric entered. re-enter variables a, b and c:\n";
    }
    quadratic(a, b, c);
    keep_window_open();
    return 0;
}
catch (std::exception& e)
{
    std::cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch (...)
{
    std::cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;
}
