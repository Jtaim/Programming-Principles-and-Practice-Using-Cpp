//written by Jtaim
//date 7 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 10
A program that reads and stores a series of doubles.
Ask user to enter number(N) of doubles want to sum.
Create a vector of the first N doubles.
From that vector calculate the sum of those N doubles.
Also  provide a vector of the delta between delta[1] - delta[0], ..., delta[N] - delta[N-1].
Instruct user to terminate series with '|' when finished entering numbers.
Handle all inputs and provide and error N is larger than input vector
*/

#include "section5.h"

double sum_up(int, const std::vector<double> &);

int main()
try
{
    using std::cout;
    using std::cin;
    using std::endl;

    constexpr char termination{ '|' };

    cout << "Enter how many numbers that you would like to sum:\n";

    int sumHowMany{ 0 };
    while (!(cin >> sumHowMany)) {
        if (cin.bad()) {
            error("cin.bad() flag set");
        }
        cin.clear();
        cin.get();
        cout << "Invalid entry!\n";
    }
    std::vector<double> numbers;
    std::vector<double> deltas;
    cout << "Enter some numbers (press '" << termination << "' to stop)\n";
    //while loop to get numbers to place in a vector, validate and exit on an '|' entry
    while (true) {
        double number;
        // loads entered numbers into a container vector
        if (cin >> number) {
            if (numbers.size() != 0) {
                deltas.push_back(numbers.back() - number);
            }
            numbers.push_back(number);
        }
        else
        {
            if (cin.bad()) {
                error("cin.bad() flag set");
            }
            cin.clear();
            char c;
            cin >> c;
            if (c == termination) {
                break;
            }
            else {
                cout << "Invalid entry!\n";
            }
        }
    }
    if (numbers.size() >= sumHowMany) {
        auto sum = sum_up(sumHowMany, numbers);
        cout << "The sum of the first " << sumHowMany << " numbers ";
        for (auto i = numbers.begin(); i < (numbers.begin() + sumHowMany); ++i) {
            if ((sumHowMany - 1) == (i - numbers.begin())) {
                cout << *i << " = " << sum << endl;
            }
            else {
                cout << *i << " + ";
            }
        }
        if (numbers.size() > 1)
        {
            cout << "Deltas between the numbers entered are:\n";
            for (auto i = 0; i < (sumHowMany - 1); ++i) {
                cout << numbers[i] << " - " << numbers[i + 1] << " = " << deltas[i] << endl;
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

/*	Sums a vector to the user selected number to sum.
    Inputs:		int(N)
                reference to vector of doubles

    Outputs:	vector values summed to N input elements

    Errors:		number want to sum is larger than the vector size
*/
double sum_up(int x, const std::vector<double> &numbers)
{
    double sum = 0;
    //sum the numbers
    if (numbers.size() < x)
    {
        error("not enough numbers entered to sum.\n");
    }
    for (int i = 0; i < x; i++)
    {
        sum += numbers[i];
    }
    return sum;
}
