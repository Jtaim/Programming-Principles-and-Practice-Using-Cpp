//written by Jtaim
//date 2 Apr 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 20.
Modify exercise 19 so that when you enter a name, the program will output the
corresponding score or name not found.
*/

#include "section4.h"

int main()
{
    using std::cout;
    using std::cin;

    std::string name{};
    std::vector<std::string> names{ "moe", "larry", "curly", "shemp" }; //there was 6 stooges 
    std::vector<int> scores{ 1,2,3,4 };
    cout << "Enter a name to find a score.\n";
    // collect valid data
    // just to insure 2 vectors are the same size
    while (names.size() == scores.size())
    {
        cin >> name;
        // escape if NoName or EOF
        if (cin.eof() || name == "NoName") {
            break;
        }
        else if (cin.bad()) {
            simple_error("input data error\n");
        }
        // check for name
        else
        {
            std::transform(name.begin(), name.end(), name.begin(),
                [](unsigned char c) {return static_cast<unsigned char>(::tolower(c)); });
            auto result = find(names.begin(), names.end(), name);
            // found a name match
            if (result != names.end())
            {
                auto score_to_match = scores.at(result - names.begin());
                cout << name << "'s score is " << score_to_match << ".\n";
            }
            // no name found
            else
            {
                cout << "Name not found.\n";
            }
        }
    }
    keep_window_open();
    return 0;
}
