/*
    Written by Jtaim
    Date 11 Oct 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++. Pearson Education. Kindle Edition.

    Section 11 Exercise 9
    Split the binary I/O program from section 11.3.2 into two:
    one program that converts an ordinary text file into binary and one program that reads binary and converts it to text.
    Test these programs by comparing a text file with what you get by converting it to binary and back.
*/

#include "ppp.h"

int main()
try {
    std::ifstream ifs_ascii{ "sect11_ex9.cpp" };
    if (!ifs_ascii) {
        ppp::error("could not open sect11_ex9.cpp");
    }
    std::ofstream ifs_bin{ "sect11_ex9_bin", std::ios_base::binary };
    if (!ifs_bin) {
        ppp::error("could not open sect11_ex9_bin");
    }
    for (char ch{}; ifs_ascii.get(ch); ) {
        ifs_bin << ch;
    }


    ppp::keep_window_open();
    return 0;
}
catch (std::exception & e) {
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch (...) {
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}