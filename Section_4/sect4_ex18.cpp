//written by Jtaim
//date 2 Apr 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 18.
Write a program to solve quadratic equations.
ax^2 + bx + c = 0
ax^2 + bx = -c
x^2 + bx/a = -c/a
x^2 + bx/a + (b/2a)^2 = -c/a + (b/2a)^2  complete the square
(x + (b/2a))^2 = (b^2-4ac)/4a^2
x = -b +/- sqrt(b^2-4ac)/2a
*/

#include "section4.h"

int main()
{
    std::cout << "Enter the a, b and c variables to solve the quadratic equation:" << std::endl;
    double a{ 0.0 };
    double b{ 1.0 };
    double c{ 0.0 };
    if (std::cin >> a >> b >> c) {
        double x1 = (-1.0 * b + sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
        double x2 = (-1.0 * b - sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
        std::cout << "x = " << x1 << " and x = " << x2 << std::endl;
    }
    else {
        simple_error("Entered invalid numbers");
    }

    keep_window_open();
    return 0;
}
