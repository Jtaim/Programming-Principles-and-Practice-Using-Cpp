/*
    Written by Jtaim
    Date 12 Jan 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 11 Drill 10
    Make a simple table including last name, first name, telephone number,
    and email address for yourself and at least five of your friends.
    Experiment with different field widths until you are satisfied that the table is well presented.
*/

#include "ppp.hpp"

struct Contact
{
    std::string last_name;
    std::string first_name;
    std::string phone;
    std::string email;
};

std::ostream &operator<<( std::ostream &os, const Contact &out )
{
    std::print( os, "{:30} {} {:30} {} {}",
                std::format( "{}, {}", out.last_name, out.first_name),
                "Phone:", out.phone, "Email:", out.email );
    return os;
}

int main()
try
{
    std::vector<Contact> contacts{
        { "Mint", "Mary", "1.555.555.1111", "mary.mint@ppp.com" },
        { "Basil", "Billy", "1.555.555.2222", "billy.basil@ppp.com" },
        { "Rosemary", "Raymond", "1.555.555.3333", "raymond.rosemary@ppp.com" },
        { "Cilantro", "Christine", "1.555.555.4444", "christina.cilantro@ppp.com" },
        { "Lavender", "Lawrence", "1.555.555.5555", "lawrence.lavender@ppp.com" }
    };

    for( const Contact &c : contacts )
    {
        std::cout << c << std::endl;
    }

    ppp::keep_window_open();
    return 0;
}
catch( std::exception &e )
{
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch( ... )
{
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}
