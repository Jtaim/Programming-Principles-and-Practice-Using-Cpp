/*
    Written by Jtaim
    Feb 26 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 10 Drill 1
    this is the test program Point class.
*/

#include "../includes/ppp.h"
#include "Point.h"

int main()
try{
   
    Point a;
    Point b{2,3};

    std::cout << a << "\n";
    std::cout << b << "\n";

    ppp::keep_window_open();
    return 0;
}
catch(std::exception& e){
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch(...){
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}