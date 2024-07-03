/*
    Written by Jtaim
    Date 7 June 2024
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Complete the code fragment above to make it into a program.
    Try the suggested input; then type in 1234  1234  1234  1234 Explain the results. Try other inputs to see what happens.
    If you type in 1234  4d2  2322  2322 this will print 1234  1234  1234  1234
*/

#include <ppp.hpp>

int main()
{
    int a;
    int b;
    int c;
    int d;
    std::cin >> a >> std::hex >> b >> std::oct >> c >> d;
    std::cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';

    ppp::keep_window_open();
    return 0;
}
