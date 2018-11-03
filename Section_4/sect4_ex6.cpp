//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 6.
Make a vector holding the ten string values "zero", "one", . . . "nine".
Use that in a program that converts a digit to its corresponding spelled-out value; e.g., the input 7 gives the output seven.
Have the same program, using the same input loop, convert spelled-out numbers into their digit form; e.g., the input seven gives the output 7.
*/

#include "section4.h"

int main()
{
    using std::cout;
    using std::cin;

    const std::vector<std::string> spelledNumbers{
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };
    constexpr auto termination{ '|' };

    cout << "will loop to try more.  use '|' to exit.\n";
    auto exit{ false };
    while (!exit) {
        cout << "Enter a number between 0 and 9 either spelled out or as the number.\n";
        auto number{ -1 };
        if (cin >> number) {
            if (number >= 0 && number <= 9) {
                cout << "The number entered is " << spelledNumbers[number] << "\n\n";
            }
            else {
                cout << "numbered entered could not be spelled out.\n";
            }
        }
        // check if number is spelled out
        else {
            cin.clear();
            std::string enteredNum;
            cin >> enteredNum;
            // convert to lower
            std::transform(enteredNum.begin(), enteredNum.end(), enteredNum.begin(), [](unsigned char c) {
                return static_cast<unsigned char>(tolower(c));
            });
            // check if has a spelled out number
            auto num_index = std::find(spelledNumbers.begin(), spelledNumbers.end(), enteredNum);
            if (num_index != spelledNumbers.end()) {
                cout << "The number entered is " << (num_index - spelledNumbers.begin()) << "\n\n";
            }
            // check for termination
            else {
                if (std::find(enteredNum.begin(), enteredNum.end(), termination) != enteredNum.end()) {
                    exit = true;
                }
                else {
                    cout << "could not find number.\n";
                }
            }
        }
    }
    cout << "bye\n";
    keep_window_open();
    return 0;
}
