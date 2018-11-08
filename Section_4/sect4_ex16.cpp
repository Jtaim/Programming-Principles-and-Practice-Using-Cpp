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
    using vType = std::vector<int>;
    std::cout << "Enter a sequence of numbers to find the MODE. (use '|' to indicate last number)" << std::endl;

    vType sequence;  // vector to hold input sequence
    vType::value_type enteredValue;
    while (std::cin >> enteredValue) {
        sequence.push_back(enteredValue);
    }

    if (!sequence.empty()) {
        std::sort(sequence.begin(), sequence.end());
        vType::value_type mode{};
        vType::difference_type cnt{};

        vType::value_type temp{};
        for (auto i = sequence.begin(); i < sequence.end(); ++i) {
            // first index is default mode and count
            if (i == sequence.begin()) {
                temp = *i;
                mode = temp;
                cnt = std::count(i, sequence.end(), mode);
            }
            // if next not same
            else if (temp != *i) {
                temp = *i;
                auto t_cnt = std::count(i, sequence.end(), temp);
                // check if we have new higher count
                if (cnt <= t_cnt) {
                    cnt = t_cnt;
                    mode = temp;
                }
            }
        }

        // print out the MODE
        if (cnt > 1) {
            std::cout << "The MODE of entered sequence is " << mode << ".\n";
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
