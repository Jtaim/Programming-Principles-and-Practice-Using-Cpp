//written by Jtaim
//date 2 Apr 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 16.
A program that finds the mode of a set of positive integers
The "mode" is the value that occurs most often.
If no number is repeated, then there is no mode for the list.
Refer to drill 3
*/

#include "section4.h"

int main()
{
    using std::cout;
    using std::cin;

    std::vector<int> pos_ints;  // hold numbers to check mode
    cout << "Enter a set of positive integers so can find the MODE. (use any non number to exit)\n";
    auto exit{ false };
    while (!exit) {
        auto number{ -1 };
        while ((cin >> number) && number > 0) {
            pos_ints.push_back(number);
        }
        if (!cin.good()) {
            exit = true;
            break;
        }
        else {
            cout << "must enter positive numbers.\n";
        }
    }
    if (!pos_ints.empty()) {
        std::sort(pos_ints.begin(), pos_ints.end());
        auto cnt{ 0U };
        auto temp{ -1 };
        auto mode{ 0 };
        for (auto i : pos_ints) {
            if (temp != i) {
                temp = i;
                auto t_cnt = std::count(pos_ints.begin(), pos_ints.end(), i);
                if (cnt <= t_cnt) {
                    cnt = static_cast<unsigned>(t_cnt);
                    mode = i;
                }
            }
        }

        // print out the MODE
        if (cnt > 1) {
            cout << "The MODE of entered integers is " << mode << ".\n";
            cout << mode << " was found " << cnt << " times.\n";
        }
        else {
            cout << "There is no MODE from this set.\n";
        }
        cout << "The sorted entered numbers:\n";
        int j = 1;
        // print out the entered numbers
        for (auto x : pos_ints) {
            //10 per row
            if (j % 10) {
                cout << x << '\t';
            }
            else {
                cout << x << '\n';
            }
            j++;
        }
    }
    else {
        cout << "nothing entered\n";
    }
    cout << '\n';
    keep_window_open();
    return 0;
}
