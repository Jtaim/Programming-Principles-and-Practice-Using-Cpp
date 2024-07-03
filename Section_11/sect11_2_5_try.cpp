/*
    Written by Jtaim
    Date 7 June 2024
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Make a simple table including the last name, first name, telephone number, and email address for yourself
    and at least five of your friends.
    Experiment with different field widths until you are satisfied that the table is well presented.
*/

#include <ppp.hpp>

struct contact
{
    std::string last_name;
    std::string first_name;
    std::string phone;
    std::string email;

    friend std::ostream &operator << ( std::ostream &os, const contact &out );
};

int main()
{
    std::vector<contact> contacts{
        {"Jennings","Nina", "1.123.456.7890", "Nina.Jennings@abc.com"},
        {"Stevenson", "Jacey", "1.123.456.7890", "Jacey.Stevenson@cppreference.com"},
        {"Middleton", "Lucy", "1.123.456.7890", "Lucy.Middleton@madeupcompany.com"},
        {"Vang", "Ariel", "1.123.456.7890", "Ariel.Vang@VangEnterprises.com"},
        {"Nunez", "Andreas", "1.123.456.7890", "Andreas.Nunez@Contact5.net"}
        };

    for( const contact &c : contacts )
    {
        std::cout << c << std::endl;
    }

    ppp::keep_window_open();
    return 0;
}

std::ostream &operator<<( std::ostream &os, const contact &out )
{
    os << std::left
        << std::setw( 11 ) << "Last Name:"
        << std::setw( 15 ) << out.last_name
        << std::setw( 12 ) << "First Name:"
        << std::setw( 15 ) << out.first_name
        << std::setw( 7 ) << "Phone:"
        << std::setw( 20 ) << out.phone
        << std::setw( 7 ) << "Email:"
        << std::setw( 40 ) << out.email;
    return os;
}
