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
    using pType = std::pair<std::string, double>;
    pType name_score;
    std::vector<pType> ranks{ {"Moe",1}, {"Larry",2}, {"Curly", 3},{"Shemp",4 } };

    std::cout << "Enter a name to find a score.\n";
    for (auto i : ranks) {
        std::cout << i.first << ", ";
    }
    std::cout << std::endl;

    while (true) {
        std::string name;
        std::cin >> name;
        // escape if NoName or EOF
        if (std::cin.eof() || name == "NoName") {
            break;
        }

        // set name so first letter is capitalized and rest lower case
        name[0] = static_cast<unsigned char>(toupper(name[0]));
        std::transform(name.begin() + 1, name.end(), name.begin() + 1,
            [](unsigned char c) {return static_cast<unsigned char>(::tolower(c)); });

        // is name in list
        auto itr = ranks.begin();
        for (; itr < ranks.end(); ++itr) {
            if (itr->first == name) {
                std::cout << name << "'s score is " << itr->second << ".\n";
                break;
            }
        }
        // see if no match
        if (itr == ranks.end()) {
            std::cout << "Name not found.\n";
        }
    }

    keep_window_open();
    return 0;
}
