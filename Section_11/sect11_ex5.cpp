/*
    Written by Jtaim
    Date 21 Sept 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++. Pearson Education. Kindle Edition.

    Section 11 Exercise 5
    Write a program that reads strings and for each string outputs the character classification of each character,
    as defined by the character classification functions presented in section 11.6.
    Note that a character can have several classifications (e.g., x is both a letter and an alphanumeric).
*/

#include "ppp.h"

std::vector<std::pair<int(*)(int), std::string>> ccf{
{std::iscntrl,"control"},
{std::isprint,"print"},
{std::isspace,"space"},
{std::isblank,"blank"},
{std::isgraph,"graph"},
{std::ispunct,"punctuation"},
{std::isalnum,"number"},
{std::isalpha,"alpha_numeric"},
{std::isupper,"upper_case"},
{std::islower,"lower_case"},
{std::isdigit,"digit"},
{std::isxdigit,"hex_digit"}
};

int main()
try {
    std::ifstream ifs{"sect11_ex5.cpp"};
    for(char c{}; ifs.get(c); ) {
        std::cout << c << " (int)c " << std::hex << std::showbase << static_cast<int>(c) << " is a ";
        for(auto f : ccf) {
            if(f.first(static_cast<unsigned char>(c))) {
                std::cout << f.second << " ";
            }
        }
        std::cout << "\n";
    }
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