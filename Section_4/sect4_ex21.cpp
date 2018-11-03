//written by Jtaim
//date 2 Apr 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 21.
Modify exercise 19 so that when you enter an integer, the program will output all the
names with that score or score not found.
*/

#include "section4.h"

int main()
{
    using namespace std;

    std::vector<std::string> names{ "moe", "larry", "curly", "shemp" }; //there was 6 stooges 
    vector<int> scores{ 1,2,3,3 };
    cout << "Enter a name to find a score.\n";
    // collect valid data
    // just to insure 2 vectors are the same size
    while (names.size() == scores.size())
    {
        auto score{ 0 };
        cin >> score;
        // escape if EOF
        if (cin.eof()) {
            break;
        }
        // redo if bad input non number for score
        if (cin.fail()) {
            cout << "Entered invalid score.  Please reenter.\n";
            cin.clear();
            cin.ignore(UINT8_MAX, '\n');
        }
        else if (cin.bad()) {
            simple_error("input data error\n");
        }
        // check for name
        else {
            auto result = find(scores.begin(), scores.end(), score);
            // found a name match
            if (result != scores.end()) {
                while (result != end(scores)) {
                    auto name_to_score = names.at(result - scores.begin());
                    cout << name_to_score << "'s score is " << score << ".\n";
                    // update to find additional names matching that score
                    result = find(result + 1, end(scores), score);
                }
            }
            else {
                cout << "Name not found.\n";
            }
        }
    }
    keep_window_open();
    return 0;
}
