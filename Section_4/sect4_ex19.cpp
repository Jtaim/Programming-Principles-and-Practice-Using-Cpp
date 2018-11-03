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
    using std::cout;
    using std::cin;

    std::string name;
    auto score{ 0 };
    std::vector<decltype(name)> names;
    std::vector<decltype(score)> scores;
    cout << "Enter names and scores:\n";
    // collect valid data
    while (true) {
        cin >> name >> score;
        // escape if NoName or EOF
        if (cin.eof() || (name == "NoName" && score == 0)) {
            break;
        }
        // redo if bad input non number for score
        else if (cin.fail()) {
            cout << "Entered invalid name or score.  Please reenter.\n";
            cin.clear();
            cin.ignore(UINT8_MAX, '\n');
        }
        else if (cin.bad()) {
            simple_error("input data error\n");
        }
        else {
            std::transform(name.begin(), name.end(), name.begin(),
                [](unsigned char c) {return static_cast<unsigned char>(::tolower(c)); });
            auto result = names.begin();
            if (names.size() != 0) {
                result = find(names.begin(), names.end(), name);
            }
            if (result != names.end()) {
                simple_error("Entered duplicate name.\n");
            }
            else {
                names.push_back(name);
                scores.push_back(score);
            }
        }
    }
    if (names.size() != 0) {
        // print contents to screen
        for (auto i = names.begin(); i < names.end(); ++i) {
            cout << *i << " " << scores.at(i - names.begin()) << std::endl;
        }
    }
    keep_window_open();
    return 0;
}
