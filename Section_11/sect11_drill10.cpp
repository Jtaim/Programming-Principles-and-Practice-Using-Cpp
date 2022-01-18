/*
    Written by Jtaim
    Date 12 Jan 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 11 Drill 10
    Make a simple table including last name, first name, telephone number,
    and email address for yourself and at least five of your friends.
    Experiment with different field widths until you are satisfied that the table is well presented.
*/

#include "ppp.h"

constexpr int setIndent{2};

struct Contact
{
    std::string last_name;
    std::string first_name;
    std::string phone_number;
    std::string email;
};

std::ostream& operator<<(std::ostream &os, const Contact &c)
{
    using std::setw;
    os << setw(7) << "Name:" << setw(setIndent) << "" << c.first_name << " " << c.last_name << "\n"
        << setw(7) << "Phone:" << setw(setIndent) << "" << c.phone_number << "\n"
        << setw(7) << "Email:" << setw(setIndent) << "" << c.email << "\n\n";
    return os;
}

int main()
try {
    Contact c1 = {"Mint", "Mary", "1.555.555.1111", "mary.mint@ppp.com"};
    Contact c2 = {"Basil", "Billy", "1.555.555.2222", "billy.basil@ppp.com"};
    Contact c3 = {"Rosemary", "Raymond", "1.555.555.3333", "raymond.rosemary@ppp.com"};
    Contact c4 = {"Cilantro", "Christine", "1.555.555.4444", "christina.cilantro@ppp.com"};
    Contact c5 = {"Lavender", "Lawrence", "1.555.555.5555", "lawrence.lavender@ppp.com"};

    std::cout << c1 << c2 << c3 << c4 << c5;

    ppp::keep_window_open();
    return 0;
}
catch(std::exception &e) {
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch(...) {
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}