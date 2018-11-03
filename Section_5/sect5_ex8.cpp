//written by Jtaim
//date 7 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 8
A program that reads and stores a series of integers.
Ask user to enter number(N) of integers want to sum.
Create a vector of the first N integers.
From that vector calculate the sum of those N integers.
Instruct user to terminate series with '|' when finished entering numbers.
Handle all inputs and provide and error N is larger than input vector
*/

#include "section5.h"

int main()
try
{
    using std::cout;
    using std::cin;
    using std::endl;

    constexpr char termination{ '|' };

    cout << "Enter how many integers that you would like to sum:\n";

    int sumHowMany{ 0 };
    while (!(cin >> sumHowMany)) {
        if (cin.bad()) {
            error("cin.bad() flag set");
        }
        cin.clear();
        cin.get();
        cout << "Invalid entry!\n";
    }
    std::vector<int> numbers;
    cout << "Enter some integers (press '" << termination << "' to stop)\n";
    //while loop to get integers to place in a vector, validate and exit on an '|' entry
    while (true) {
        int number{ 0 };
        // loads entered numbers into a container vector
        if (cin >> number) {
            numbers.push_back(number);
        }
        else
        {
            if (cin.bad()) {
                error("cin.bad() flag set");
            }
            cin.clear();
            char c;
            cin.get(c);
            if (c == termination) {
                break;
            }
            else {
                cout << "Invalid entry!\n";
            }
        }
    }
    if (numbers.size() >= sumHowMany) {
        int sum{ 0 };
        cout << "The sum of the first " << sumHowMany << " numbers ";
        for (auto i = numbers.begin(); i < (numbers.begin() + sumHowMany); ++i) {
            sum += *i;
            if ((sumHowMany - 1) == (i - numbers.begin())) {
                cout << *i << " = " << sum << endl;
            }
            else {
                cout << *i << '+';
            }
        }
    }
    else {
        error("not enough integers entered to sum.\n");
    }
    keep_window_open();
    return 0;
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
