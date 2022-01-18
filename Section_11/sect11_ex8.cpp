/*
    Written by Jtaim
    Date 28 Sept 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++. Pearson Education. Kindle Edition.

    Section 11 Exercise 8
    Write a program that replaces punctuation with whitespace.
    Consider . (dot), ; (semicolon), , (comma), ? (question mark), - (dash), ' (single quote) punctuation characters.
    Don’t modify characters within a pair of double quotes (").
    For example, " - don't use the as-if rule." becomes " don t use the as if rule ".

    Modify the program from the previous exercise so that it replaces don't with do not, can't with cannot, etc.;
    leaves hyphens within words intact (so that we get “ do not use the as-if rule ”); and converts all characters to lower case.
    https://en.wikipedia.org/wiki/Contraction_(grammar)
    https://www.grammarly.com/blog/contractions/
    https://grammar.yourdictionary.com/style-and-usage/using-contractions.html
    https://www.thoughtco.com/contractions-commonly-used-informal-english-1692651

    Use the program from the previous exercise to make a dictionary (as an alternative to the approach in Section 11.7).
    Run the result on a multi-page text file, look at the result, and see if you can improve the program to make a better dictionary.
*/

#include "ppp.h"
#include "Punct_stream.h"



int main()
try {
    Punct_stream ps{std::cin};  //ps reads from cin
    ps.whitespace(".;,?'-");
    ps.case_sensitive(false);

    std::cout << "Please enter a string\n";
    for(std::string str; ps >> str; ) {
        std::cout << str << " ";
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
