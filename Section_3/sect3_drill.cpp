//written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition


/**
 * Section 3 Drill. This drill is to write a program that produces a
 * simple form letter based on user input.
 */

#include "section3.h"

int main()
{
    using namespace std;

    const unsigned minAge{ 0 };
    const unsigned maxAge{ 130 };

    cout << "Enter the name of the person you want to write to:\n";
    string first_name;
    cin >> first_name;
    cout << "Dear " << first_name << ",\n";
    cout << "\tHow are you? I am fine. I'm writing a simple program in C++\n";
    cout << "Enter a friends name:\n";
    cin >> first_name;
    cout << "Have you seen " << first_name << " lately?\n";
    cout << "What is your friends gender?" << "(Enter m for male and f for female)\n";
    char gender{ 'o' };
    //check for correct entry
    while (cin >> gender)
    {
        //reason for cast is that the return from tolower() is int and gives conversion warning
        gender = static_cast<char>(tolower(gender));
        if (gender == 'm') {
            cout << "If you see " << first_name << " ask him to call me.\n";
            break;
        }
        else if (gender == 'f') {
            cout << "If you see " << first_name << " ask her to call me.\n";
            break;
        }
        cout << "unrecognized gender " << gender << ", please reenter: ";
    }

    cout << "How old are you?\n";
    int age{ 0 };
    //check for valid age and valid cin to int
    if (cin >> age && age > minAge && age < maxAge) {
        cout << "I hear you just had a birthday and you are " << age << " years old.\n";
        if (age < 12) { cout << "Next year you will be " << age + 1 << ".\n"; }
        else if (age == 17) { cout << "Next year you will be able to vote.\n"; }
        else if (age > 70) { cout << "I hope you are enjoying retirement.\n"; }
        cout << "Yours sincerely,\n\n\nJ\n";
    }
    else {
        simple_error("you're kidding!");
    }

    keep_window_open();
    return 0;
}
