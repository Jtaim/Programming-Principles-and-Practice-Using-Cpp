//written by Jtaim
//date 26 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Try This 4.4.1.3
program that converts yen, euro, pound, yuan, and kroner into dollar
*/

#include "section4.h"

int main()
{
    using std::cout;
    using std::endl;
    using std::cin;

    const std::vector<std::pair<const std::string, const double>> convertRate{
        {"yen", 113.21},
        {"euro", 0.88},
        {"pound", 0.77},
        {"danish krone", 6.55},
        {"yuan", 6.89}
    };

    cout << "Please enter an amount followed by a currency to convert to dollar:\n";
    for (auto i = convertRate.begin(); i < convertRate.end(); ++i) {
        if (i + 1 == convertRate.end()) {
            cout << "or " << i->first << endl;
        }
        else {
            cout << i->first << ", ";
        }
    }

    // get currency amount
    double amount{ 1.0 };
    if (!(cin >> amount)) {
        simple_error("entered amount unknown");
    }

    // get currency to covert
    std::string currency;
    cin >> std::ws; // delete any preceding whitespace
    std::getline(cin, currency);
    // change entered currency to lower case
    for (auto &c : currency) {
        c = static_cast<char>(tolower(c));
    }

    // find conversion type
    auto conversion{ convertRate.size() };
    for (auto i = convertRate.begin(); i < convertRate.end(); ++i) {
        if (i->first == currency) {
            conversion = i - convertRate.begin();
            break;
        }
    }

    // get conversion amount
    // could eliminate the switch statement and do all in the above for loop
    switch (conversion) {
    case 0:
        cout << amount << " " << currency << " == $" << 1 / convertRate.at(conversion).second * amount << endl;
        break;
    case 1:
        cout << amount << " " << currency << " == $" << 1 / convertRate.at(conversion).second * amount << endl;
        break;
    case 2:
        cout << amount << " " << currency << " == $" << 1 / convertRate.at(conversion).second * amount << endl;
        break;
    case 3:
        cout << amount << " " << currency << " == $" << 1 / convertRate.at(conversion).second * amount << endl;
        break;
    case 4:
        cout << amount << " " << currency << " == $" << 1 / convertRate.at(conversion).second * amount << endl;
        break;
    default:	simple_error("unknown conversion type");
    }

    keep_window_open();
}
