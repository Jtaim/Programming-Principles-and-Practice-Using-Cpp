//written by Jtaim
//date 2 Apr 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 17.
finds the min, max and mode of a sequence of strings
*/

#include "section4.h"

int main()
{
    using std::cout;
    using std::cin;

    std::vector<std::string> input_strings{};  // hold numbers to check mode
    std::string input_string{};
    cout << "Enter a set of strings to find the min, max and mode.\n";
    cout << "EOF to exit.\n\n";
    while (true) {
        if (cin >> input_string) {
            std::transform(input_string.begin(), input_string.end(), input_string.begin(),
                [](unsigned char c) {return static_cast<unsigned char>(tolower(c)); });
            input_strings.push_back(input_string);
        }
        else { break; }
    }
    std::sort(input_strings.begin(), input_strings.end());
    auto count{ 0U };
    std::string temp;
    std::string mode;
    for (auto i : input_strings) {
        if (temp != i) {
            temp = i;
            auto t_cnt = std::count(input_strings.begin(), input_strings.end(), i);
            if (count <= t_cnt) {
                count = static_cast<unsigned>(t_cnt);
                mode = i;
            }
        }
    }
    // print out the MODE
    if (count > 1) {
        cout << "The MODE of entered strings is " << mode << ".\n";
        cout << mode << " was found " << count << " times.\n";
    }
    else {
        cout << "There is no MODE from this set.\n";
    }
    cout << "Maximum string entered was " << input_strings.back() << "\n";
    cout << "Minimum string entered was " << input_strings.front() << "\n\n";
    for (auto x : input_strings) {
        cout << x << '\n';
    }
    keep_window_open();
    return 0;
}
