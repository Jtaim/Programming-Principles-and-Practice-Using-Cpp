//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 7.
Modify the "mini calculator from exercise 5 to accept (just) single-digit numbers written as either digits
or spelled out.
*/

#include "section4.h"

bool getNumber(int &arg, const std::vector<std::string> &spelledNumbers);

int main()
{
    const std::vector<char> ops{ '+','-','*','/' };
    const std::vector<std::string> spelledNumbers{
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };

    std::cout << "Enter 2 numbers and an operation (+, -, *, /).\n";
    std::cout << "Number entered must be between 0 and 9 either spelled out or as the number.\n\n";

    int arg1{ 0 }, arg2{ 0 };
    if (!getNumber(arg1, spelledNumbers) || !getNumber(arg2, spelledNumbers)) {
        simple_error("incorrect numbers entered.\n");
    }

    char op;
    std::cin >> op;
    double result{ 0.0 };
    switch (op) {
    case '+':
        result = arg1 + arg2;
        break;
    case '-':
        result = arg1 - arg2;
        break;
    case '*':
        result = arg1 * arg2;
        break;
    case '/':
        if (arg2 != 0) {
            result = arg1 / arg2;
        }
        else {
            simple_error("division by zero is not allowed.\n");
        }
        break;
    default:
        simple_error("incorrect operator entered.\n");
    }

    std::cout << arg1 << " " << op << " " << arg2 << " = " << result << std::endl;

    std::cout << "Bye\n";
    keep_window_open();
    return 0;
}

bool getNumber(int &arg, const std::vector<std::string> &spelledNumbers)
{
    bool isGood{ false };
    if (!(std::cin >> arg)) {
        // check if number is spelled out
        std::cin.clear();
        std::string spelledNumber;
        std::cin >> spelledNumber;
        // convert to lower
        std::transform(spelledNumber.begin(), spelledNumber.end(), spelledNumber.begin(), [](unsigned char c) {
            return static_cast<unsigned char>(tolower(c));
        });
        // check if has a spelled out number
        auto spelledIndex = std::find(spelledNumbers.begin(), spelledNumbers.end(), spelledNumber);
        if (spelledIndex != spelledNumbers.end()) {
            arg = static_cast<int>(spelledIndex - spelledNumbers.begin());
            isGood = true;
        }
    }
    else {
        isGood = true;
    }
    return isGood;
}
