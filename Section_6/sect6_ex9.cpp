//Written by Jtaim
//Date 2 Dec 2015
//updated 28 Dec 2016
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 6 exercise 9
read digits and compose them into integers. For example, 123 is read as the characters 1, 2, and 3.
Output of 123 is 1 hundred and 2 tens and 3 ones.
The numbers is output as int value.
Handle up to 4 digits.
terminate program with '|'.
*/

#include "section6.h"

int main()
{
    constexpr char termination = '|';
    // only have to add or subtract denominations array size and program will adjust.
    // make_array is experimental which could just declare elements then will adjust.
    constexpr std::array<const char*, 4> denomination{ "ones", "tens", "hundreds", "thousands" };
    constexpr auto maxValueSize = denomination.size();

    try {
        bool isLoopAgain = true;
        do {
            std::cout << "Enter a number up to " << maxValueSize << " digits long. Enter " << termination << " to exit\n";
            std::string number{};
            size_t itr = 0;
            while (true) {
                char digit;
                std::cin.get(digit);
                if (digit == '\n') {
                    break;
                }
                else if (!isdigit(digit)) {
                    if (digit == termination) {
                        isLoopAgain = false;
                        break;
                    }
                    error("found a non number character");
                }
                else {
                    if (itr < maxValueSize) {
                        number.push_back(digit);
                        ++itr;
                        continue;
                    }
                    error("entered number is too large");
                }
            }

            if (!number.empty()) {
                std::cout << number << " is ";
                for (size_t i{}, j{ number.size() - 1 }; i < number.size(); ++i, --j) {
                    std::cout << number[i] << " " << denomination[j]
                        << ((i < number.size() - 1) ? " and " : ".\n");
                }
            }
            else if (isLoopAgain) {
                std::cout << "no number was entered\n";
            }

            number.clear();
        } while (isLoopAgain);

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

    std::cout << "Bye";
    keep_window_open();
    return 0;
}
