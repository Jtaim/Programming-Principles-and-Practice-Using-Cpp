/*
    Written by Jtaim
    Date 24 Nov 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 11 Exercise 10
    Write a function vector<string> split(const string& s) that returns a vector of whitespace-separated substrings from the argument s.
*/

#include"ppp.h"

std::vector<std::string> split(const std::string& s);

int main()
try {
    std::string_view str{"Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition."};
    auto white_space{split(str.data())};
    
    for(auto s : white_space) {
        std::cout << s << '\n';
    }

    ppp::keep_window_open();
    return 0;
} catch(std::exception & e) {
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
} catch(...) {
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}

std::vector<std::string> split(const std::string& s)
{
    std::vector<std::string> strings;
    std::istringstream is{s};
    for(std::string str; is >> str; ) {
            strings.push_back(str);
    }
    return strings;
}
