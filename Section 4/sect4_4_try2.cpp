//written by Jtaim
//date 21 Sept 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Try This 4.4.1.3
program that converts yen, euros, pounds, yuan, and kroner into dollars
*/

#include "section4.h" //custom header

int main()
{
    constexpr double yen_to_dollar = 120.36;	//to a dollar
    constexpr double euro_to_dollar = 0.89;
    constexpr double pound_to_dollar = 0.64;
    constexpr double krone_to_dollar = 6.68;	//danish Krone
    constexpr double yuan_to_dollar = 6.38;
    double amount = 1.0;
    char convert = '?';
    string currency = "???";
    double rate = 1.0;
    cout << "Please enter an amount and currency to convert ('$' is to dollars 'o' to other:\n";
    cin >> amount >> currency >> convert;
    if (currency == "yen")
        rate  = yen_to_dollar;
    else if (currency == "euro")
        rate = euro_to_dollar;
    else if (currency == "pound")
        rate = pound_to_dollar;
    else if (currency == "krone")
        rate = krone_to_dollar;
    else if (currency == "yuan")
        rate = yuan_to_dollar;
    else
        {
            cout << "Sorry, I don't know a currency called " << currency << endl;
			keep_window_open();
            exit(0);
        }
            
    switch(convert)
    {
    case '$':
        
        cout << amount << " " << currency << " == $" << 1/rate*amount << endl;
        break;
    case 'o':
        cout << "$" << amount << " == " << currency << " " << rate*amount << endl;
        break;
    default:
        cout << "Sorry don't know how to convert.  Please select correct command.\n";
    }
	keep_window_open();
}