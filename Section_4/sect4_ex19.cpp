//written by Jtaim
//date 2 Apr 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 19.
A program where you first enter a set of name-and-value pairs, such as Joe 17 and Barbara 22.
For each pair, add the name to a vector called names and the number to a vector called scores
(in corresponding positions, so that if names[7]=="Joe" then scores[7]==17).
Terminate input with NoName 0.
Check that each name is unique and terminated with an error message if a name is entered twice.
Write out all the (name, score) pairs, one per line.
*/

#include "section4.h"

int main()
{
    using pType = std::pair<std::string, double>;
    pType name_score;
    std::vector<pType> ranks;

    std::cout << "Enter names and scores:\n";
    while (true) {
        std::cin >> name_score.first >> name_score.second;
        // break if EOF and !(NoName and 0))
        if (std::cin.good() && !(name_score.first == "NoName" && name_score.second == 0)) {
            std::transform(name_score.first.begin(), name_score.first.end(), name_score.first.begin(),
                [](unsigned char name) { return static_cast<unsigned char>(::tolower(name)); });
            ranks.push_back(name_score);
        }
        else {
            break;
        }
    }

    if (!ranks.empty()) {
        // check for duplicates
        for (const auto p : ranks) {
            std::vector<pType>::size_type cnt{};
            for (const auto check : ranks) {
                if (p.first == check.first) {
                    if (cnt > 0) {
                        simple_error("found a duplicated name");
                    }
                    ++cnt;
                }
            }
        }

        // print contents to screen
        for (const auto i : ranks) {
            std::cout << "name: " << i.first << "\tscore: " << i.second << std::endl;
        }
    }
    else {
        std::cout << "nothing entered\n";
    }

    keep_window_open();
    return 0;
}
