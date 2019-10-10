/*
    Written by Jtaim
    Date 12 Jan 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 11 Drill 9
    Write some code to print the number 1234567.89 three times, first using default float, then fixed, then scientific forms.
    Which output form presents the user with the most accurate representation?
    Explain why.
*/

#include "ppp.h"

int main()
try {
    double number{123456.89};

    std::cout << "The number in default: " << number << '\n'
        << "The number in fixed: " << std::fixed << number << '\n'
        << "The number in scientific: " << std::scientific << number << '\n'
        << "The number in default: " << std::defaultfloat << number << '\n';

    // fixed seems to present the number more accurately.

    ppp::keep_window_open();
    return 0;
}
catch(std::exception &e) {
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch(...) {
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}