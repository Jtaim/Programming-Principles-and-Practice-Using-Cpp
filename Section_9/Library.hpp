#pragma once

#include <vector>
#include "Book.hpp"
#include "Patron.hpp"
#include "Chrono.hpp"

namespace library
{
    class Library
    {
    public:
        struct Transaction
        {
            Book book;
            Patron patron;
            Chrono::Date date;
            Transaction( Book b, Patron p, Chrono::Date d )
                : book( b ), patron( p ), date( d )
            {}
        };

        Library();

        void add_book();
        void add_patron();
        void check_out_book( Book& b, Patron& p );
        std::vector<std::pair<std::string, double>> get_outstanding_fees();

    private:
        std::vector<Book> m_books;
        std::vector<Patron> m_patrons;
        std::vector<Transaction> transactions;

        std::string get_string();
    };

}
