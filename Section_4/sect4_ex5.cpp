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

int main()
{
    const std::vector<char> ops{ '+','-','*','/' };

    std::cout << "Enter 2 numbers and an operation (+, -, *, /).\n";
    double arg1{ 0.0 }, arg2{ 0.0 };
    if (!(std::cin >> arg1) || !(std::cin >> arg2)) {
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

    std::cout << "\nBye\n";
    keep_window_open();
    return 0;
}
