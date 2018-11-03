//written by Jtaim
//date 22 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 3.3 try this exercise
Get the “name and age” example to run.
Then, modify it to write out the age in months:
read the input in years and multiply (using the * operator) by 12.
Read the age into a double to allow for children who can be very
proud of being five and a half years old rather than just five.
*/

#include "section3.h"	//custom header

int main()
{
    std::cout << "Please enter your first name: ";
    std::string first_name = "???";
    std::cin >> first_name;

    std::cout << "Please enter your age: ";
    double age = 0.0;
    while (std::cin >> age) {
        if (age < 0.0 || age > 130.0) {
            std::cout << "bad age entered! Try again" << std::endl;
        }
        else {
            break;
        }
    }
    double age_months = age * 12.0;
    std::cout << "Hello, " << first_name
        << " (age " << age << ")"
        << "(age in months " << age_months << ")\n";

    keep_window_open();
}
