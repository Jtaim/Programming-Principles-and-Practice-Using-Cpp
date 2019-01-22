/*
    Written by Jtaim
    Date 20 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 9 Exercise 9
    Test the Design of a Library class under library namespace
    this file is to test the library class
*/

#include"../includes/ppp.h"

#include "Library.h"

const std::stringstream patrons{
        "Pappa \"Too Hard\" Bear,\
        0.0\
        y\
        Momma \"Too Soft\" Bear,\
        1.15\
        y\
        Baby \"Just Right\" Bear,\
        2.23\
        y\
        Goldie Locks,\
        0.0\
        n"};
const std::stringstream books{
        "0-321-99278-4,\
        Programming Principles and Practices Using C++ Second Edition,\
        Bjarne Stroustrup,\
        2014\
        y\
        0-13-110370-9,\
        The C Programming Language Second Edition,\
        Brian W.Kernighan and Dennis M.Ritchie,\
        1988\
        n"};

int main()
try{
    using library::Patron;
    using library::Book;

    library::Library LearnCppLibrary;

    auto rcbuf = std::cin.rdbuf(); // backup cin buffer
    std::cin.set_rdbuf(patrons.rdbuf()); // comment line to enter patrons manually

    char c{};
    do{
        std::cout << "Enter patron:\n";
        LearnCppLibrary.add_patron();

        std::cout << "Enter another patron name (y,n):\n";
        std::cin >> c;
        std::tolower(c);
    } while(c == 'y');

    std::cin.set_rdbuf(books.rdbuf()); // comment line to enter books manually
    do{

        std::cout << "Enter book:\n";
        LearnCppLibrary.add_book();
        std::cout << "Enter another book (y,n):\n";
        std::cin >> c;
        std::tolower(c);
    } while(c == 'y');

    std::cin.set_rdbuf(rcbuf);  // reset cin buffer

    Book book1("0-321-99278-4", "Programming Principles and Practices Using C++ Second Edition", "Bjarne Stroustrup", 2014);
    Book book2("0-13-110370-9", "The C Programming Language Second Edition", "Brian W.Kernighan and Dennis M.Ritchie", 1988);
    Book book3("0-201-70073-5", "The C++ Programming Language", "Bjarne Stroustrup", 2000);

    Patron patron1("Pappa \"Too Hard\" Bear", 1);
    Patron patron2("Momma \"Too Soft\" Bear", 2);
    Patron patron3("Baby \"Just Right\" Bear", 3);
    Patron patron4("Goldie Locks", 4);
    Patron patron5("Jtaim", 5);

    LearnCppLibrary.check_out_book(book1, patron4);

    //LearnCppLibrary.check_out_book(book1, patron1);

    //LearnCppLibrary.check_out_book(book2, patron3);

    //LearnCppLibrary.check_out_book(book3, patron2);

    //LearnCppLibrary.check_out_book(book2, patron5);

    LearnCppLibrary.check_out_book(book2, patron1);

    const auto gof{LearnCppLibrary.get_outstanding_fees()};
    std::cout << "\n\nList of names with outstanding fees:\n";
    for(auto f : gof){
        std::cout << f.first << " : " << f.second << '\n';
    }

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