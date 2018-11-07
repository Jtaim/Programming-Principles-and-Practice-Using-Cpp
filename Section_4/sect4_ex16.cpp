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
    std::vector<int> numbers;  // hold numbers to check mode
    std::cout << "Enter a set of positive integers so can find the MODE. (use '|' to indicate last number)" << std::endl;

    while (true) {
        int number{ -1 };
        while ((std::cin >> number) && number > 0) {
            numbers.push_back(number);
        }
        if (!std::cin.good()) {
            break;
        }
        else {
            std::cout << "must enter positive numbers." << std::endl;
        }
    }

    if (!numbers.empty()) {
        std::sort(numbers.begin(), numbers.end());
        int mode{ 0 };
        int temp{ -1 };
        int cnt{ 0 };

        for (auto i = numbers.begin(); i < numbers.end(); ++i) {
            if (temp != *i) {
                temp = *i;
                auto t_cnt = std::count(i, numbers.end(), *i);
                if (cnt <= t_cnt) {
                    cnt = static_cast<int>(t_cnt);
                    mode = *i;
                }
            }
        }

        // print out the MODE
        if (cnt > 1) {
            std::cout << "The MODE of entered integers is " << mode << ".\n";
            std::cout << mode << " was found " << cnt << " times.\n";
        }
        else {
            std::cout << "There is no MODE from this set.\n";
        }
    }
    else {
        std::cout << "nothing entered\n";
    }

    std::cout << std::endl;
    keep_window_open();
    return 0;
}
