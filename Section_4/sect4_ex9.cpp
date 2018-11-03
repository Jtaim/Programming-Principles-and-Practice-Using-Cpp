//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 9.
 Try to calculate the number of rice grains that the inventor asked for in exercise 8 above.
 You'll find that the number is so large that it won't fit in an int or a double.
 Observe what happens when the number gets too large to represent exactly as an int and as a double.
 What is the largest number of squares for which you can calculate the exact number of grains (using an int)?
 What is the largest number of squares for which you can calculate the approximate number of grains (using a double)?
*/

#include "section4.h"

int main()
{
    using std::cout;
    using std::endl;

    auto const MAX_SQUARES{ 64 };

    auto n_grains{ 0ULL };
    auto d_grains{ 0.0L };

    cout << "The maximum number represented int on this PC is " << INT_MAX << endl;
    cout << "The maximum number represented double on this PC is " << DBL_MAX << endl;
    cout << "The maximum number represented unsigned int on this PC is " << UINT_MAX << endl;
    cout << "The maximum number represented long int on this PC is " << LONG_MAX << endl;
    cout << "The maximum number represented unsigned long int on this PC is " << ULONG_MAX << endl;
    cout << "The maximum number represented long long int on this PC is " << LLONG_MAX << endl;
    cout << "The maximum number represented unsigned long long int on this PC is " << ULLONG_MAX << endl;
    cout << "The maximum number represented long double on this PC is " << LDBL_MAX << "\n\n";
    for (int square = 0; square < MAX_SQUARES; square++) {
        //powers of 2 will provide double of previous number 2^0=1, 2^1=2, 2^2=4 2^3=8 ...
        n_grains += static_cast<decltype(n_grains)>(pow(2, square));
        cout << "square " << square + 1 << " has " << n_grains << " grains as " << typeid(n_grains).name() << ".\n\n";
        d_grains += pow(2, square);
        cout << "square " << square + 1 << " has " << d_grains << " grains as " << typeid(d_grains).name() << ".\n\n";
    }
    keep_window_open();
    return 0;
}
