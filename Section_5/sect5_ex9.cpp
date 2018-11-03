//written by Jtaim
//date 7 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 9
A program that reads and stores a series of integers.
Ask user to enter number(N) of integers want to sum.
Create a vector of the first N integers.
From that vector calculate the sum of those N integers.
Instruct user to terminate series with '|' when finished entering numbers.
Handle all inputs and provide and error N is larger than input vector

Added overflow error when summing
*/

#include "section5.h"

int sum_up(int s, const std::vector<int> &vn);

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
        int number;
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

/*	Sums a vector to the user selected number to sum.
    Inputs:		int
                reference to vector of integers

    Outputs:	vector values summed to input int elements

    Errors:		number want to sum is larger than the vector size
                if the sum of the element cause and int type overflow
*/
int sum_up(int s, const std::vector<int> &vn)
{
    int sum = 0;
    if (vn.size() < s) {
        error("not enough integers entered to sum.\n");
    }
    else {	//sum the numbers
        for (int i = 0; i < s; i++) {
            if ((vn[i] > 0) && (sum > INT_MAX - vn[i])) {
                error("int overflow error");
            }
            if ((vn[i] < 0) && (sum < INT_MAX - vn[i])) {
                error("int overflow error");
            }
            sum += vn[i];
        }
    }
    return sum;
}
