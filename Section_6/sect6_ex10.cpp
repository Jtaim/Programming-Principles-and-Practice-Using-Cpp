//Written by Jtaim
//Date 9 Dec 2015
//updated 28 Dec 2016
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 6 exercise 10
Ask user for 2 numbers.
Ask if want to do permutation or combination
p(a,b) = a!/(a-b)!
c(a,b) = p(a,b)/b!
https://www.mathsisfun.com/combinatorics/combinations-permutations.html
*/

#include "section6.h"

// do factorial to a selected stop
int factoral(int start, int end)
{
    int fact = 1;
    for (auto i = start; i > (start - end); --i) {
        fact *= i;
        if ((i > 0) && (fact > INT_MAX - i) || (i < 0) && (fact < INT_MAX - i)) {
            error("int overflow error");
        }
    }
    return fact;
}

int permutation(int a, int b)
{
    if (a <= 0 || (a - b) < 0) {
        error("Negative term in the permutation.\n");
    }
    return factoral(a, b);
}

int combination(int a, int b)
{
    int c;
    c = permutation(a, b) / factoral(b, b);
    return c;
}

int main()
{
    try {
        std::cout << "Enter two numbers and first number is greater than second number.\n";
        int a{};
        int b{};
        while (!(std::cin >> a && std::cin >> b && (a > b))) {
            std::cout << "invalid entry or first number is not greater than second number, reenter\n";
            clear_cin_buffer();
        }

        std::cout << "Do you want to do a permutation (p) or combination (c)?\n";
        char p_c{};
        while (std::cin >> p_c) {
            p_c = narrow_cast<char, int>(tolower(p_c));
            if (p_c != 'p' && p_c != 'c') {
                std::cout << "Invalid permutation or combination entry, reenter\n";
            }
            else break;
        }

        int answer{};
        if (p_c == 'p') {
            answer = permutation(a, b);
        }
        else if (p_c == 'c') {
            answer = combination(a, b);
        }
        else {
            error("invalid evaluation choice.\n");
        }
        std::cout << "The " << (p_c == 'p' ? "permutation" : "combination") << " is " << answer << ".\n";
    }
    catch (std::exception& e)
    {
        std::cerr << "error: " << e.what() << '\n';
        keep_window_open();
        return 1;
    }
    catch (...)
    {
        std::cerr << "Oops: unknown exception!\n";
        keep_window_open();
        return 2;
    }

    keep_window_open();
    return 0;
}
