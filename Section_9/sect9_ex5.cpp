/*
    Written by Jtaim
    Date 20 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 9 Exercise 5
    Design and implement a Book class under library namespace
    -
*/

#include"../includes/ppp.h"

namespace book_lib
{
    class Book{
    public:
        class Invalid{};
        Book();
        Book(std::string ISBN, std::string title, std::string author, int copyright_year);

        std::string get_isbn() const { return m_isbn; }
        std::string get_title() const { return m_title; }
        std::string get_author() const { return m_author; }
        int get_copyright() const { return m_copyright_year; }
        bool is_checked_out() const { return m_checked_out; }

        void check_inout(bool cio) { m_checked_out = cio; }

    private:
        std::string m_isbn;
        std::string m_title;
        std::string m_author;
        int m_copyright_year;
        bool m_checked_out;
        bool isbn_valid() const;
    };

    Book::Book()
        : m_isbn("0-0-0-x"),
        m_title("?"),
        m_author("?"),
        m_copyright_year(9999),
        m_checked_out(false)
    {}

    Book::Book(std::string ISBN, std::string title, std::string author, int copyright_year)
        : m_isbn(ISBN), m_title(title), m_author(author), m_copyright_year(copyright_year), m_checked_out(false)
    {
        if(!isbn_valid()) throw Invalid{};
    }

    bool Book::isbn_valid() const
    {
        std::stringstream ss;
        ss << m_isbn;
        int n1{}, n2{}, n3{};
        char c1{}, c2{}, c3{}, c4{};
        ss >> n1 >> c1 >> n2 >> c2 >> n3 >> c3 >> c4;
        if(ss.good() && c1 == '-' && c2 == '-' && c3 == '-'&& isalnum(c4)){
            return true;
        }
        return false;
    }

}

int main()
try{
    book_lib::Book book("0-321-99278-4", "Programming Principles and Practices Using C++ Second Edition", "Bjarne Stroustrup", 2014);
    std::cout << "ISBN: " << book.get_isbn() << '\n'
        << "TITLE: " << book.get_title() << '\n'
        << "AUTHOR: " << book.get_author() << '\n'
        << "COPYRIGHT: " << book.get_copyright() << '\n'
        << "checked out: " << std::boolalpha << book.is_checked_out() << "\n\n";

    book.check_inout(true);
    std::cout << "ISBN: " << book.get_isbn() << '\n'
        << "TITLE: " << book.get_title() << '\n'
        << "AUTHOR: " << book.get_author() << '\n'
        << "COPYRIGHT: " << book.get_copyright() << '\n'
        << "checked out: " << std::boolalpha << book.is_checked_out() << "\n\n";

    //book_lib::Book book2("0-321_99278-4", "Programming Principles and Practices Using C++ Second Edition", "Bjarne Stroustrup", 2014);

    ppp::keep_window_open();
    return 0;
}
catch(book_lib::Book::Invalid){
    std::cerr << "exception: Invalid Book" << std::endl;
    ppp::keep_window_open();
    return 1;
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