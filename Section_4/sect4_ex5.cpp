//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 5.
Write a program that performs as a very simple calculator.
Your calculator should be able to handle the four basic math operations — add, subtract, multiply, and divide — on two input values.
Your program should prompt the user to enter three arguments: two double values and a character to represent an operation.
If the entry arguments are 35.6, 24.1, and '+', the program output should be The sum of 35.6 and 24.1 is 59.7.
*/

#include "section4.h"

bool getNumbers(double &d1, double &d2);
bool checkTerm(const char t);
void printResult(const double result);

int main()
{
    constexpr auto termination = '|';
    const std::vector<char> ops{ '+','-','*','/' };

    double arg1{ 0.0 }, arg2{ 0.0 };

    bool isComplete{ false };
    std::cout << "Enter 2 numbers and an operation (+, -, *, /). Use " << termination << " to exit.\n";
    if (!getNumbers(arg1, arg2)) {
        isComplete = checkTerm(termination);
    }
    else {
        char op;
        std::cin >> op;
        isComplete = true;
        switch (op) {
        case '+': printResult(arg1 + arg2);
            break;
        case '-': printResult(arg1 - arg2);
            break;
        case '*': printResult(arg1 * arg2);
            break;
        case '/':
            if (arg2 != 0) {
                printResult(arg1 / arg2);
            }
            else {
                simple_error("division by zero is not allowed.\n");
            }
            break;
        default:
            std::cin.putback(op);
            isComplete = checkTerm(termination);
        }
    }

    if (!isComplete) {
        std::cout << "bad number or operation entered.\n";
    }

    std::cout << "\nBye\n";
    keep_window_open();
    return 0;
}

bool getNumbers(double &d1, double &d2)
{
    if ((std::cin >> d1) && (std::cin >> d2)) {
        return true;
    }
    return false;
}

bool checkTerm(const char t)
{
    if (std::cin.eof() || std::cin.bad()) {
        return true;
    }
    std::cin.clear();
    return (std::cin.get() == t);
}

void printResult(const double result)
{
    std::cout << "Result: " << result << std::endl;
}
