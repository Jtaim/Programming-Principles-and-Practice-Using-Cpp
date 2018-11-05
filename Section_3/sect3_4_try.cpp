//written by Jtaim
//date 23 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 3.4 try this exercise
*/

#include "section3.h"	//custom header

//C++ programs start by executing the function main
int main()
{
    using std::cout;
    using std::endl;

    cout << "Please enter a value: ";
    int n{ 0 };
    std::cin >> n;

    cout << "n == " << n << endl
        << "n + 1 == " << n + 1 << endl
        << "n * 3 == " << 3 * n << endl
        << "n + n == " << n + n << endl
        << "n squared == " << n * n << endl
        << "n / 2 == " << static_cast<double>(n) / 2.0 << endl
        << "square root of n == " << static_cast<double>(std::sqrt(n)) << endl;

    keep_window_open();
    return 0;
}