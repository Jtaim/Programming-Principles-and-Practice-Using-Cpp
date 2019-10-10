/*
    Written by Jtaim
    Date 22 Sept 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++. Pearson Education. Kindle Edition.

    Section 11 Exercise 6
    Write a program that replaces punctuation with whitespace.
    Consider . (dot), ; (semicolon), , (comma), ? (question mark), - (dash), ' (single quote) punctuation characters.
    Don’t modify characters within a pair of double quotes (").
    For example, " - don't use the as-if rule." becomes " don t use the as if rule ".
*/

#include "ppp.h"

int main()
try {
    //constexpr std::string_view str{" - don't use the as-if rule. "};
    std::ostringstream oss;

    std::cout << "Please enter a string\n";
    std::string str;
    std::getline(std::cin, str);

    const auto how_big{str.size()};
    for(std::string::size_type i{}; i < how_big; ++i) {
        char ch{str.at(i)};
        switch(ch) {
            case '"':
                if((i + 2) < how_big && str.at(i + 2) == '"') {
                    oss << str.at(i + 1);
                    i += 2;
                }
                break;
            case '.':
            case ';':
            case ',':
            case '-':
            case '?':
            case '\'':
                oss << ' ';
                break;
            default:
                oss << ch;
        }
    }

    std::cout << oss.str() << "\n";

    ppp::keep_window_open();
    return 0;
}
catch(std::exception& e) {
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch(...) {
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}