//written by Jtaim
//date 2 Apr 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 21.
Modify exercise 19 so that when you enter a number, the program will output all the
names with that score or score not found.
*/

#include "section4.h"

int main()
{
    using pType = std::vector<std::pair<std::string, double>>;
    pType::value_type name_score;
    pType ranks{ {"Moe",1}, {"Larry",3}, {"Curly", 3},{"Shemp",4} };

    std::cout << "Enter a score and see all that have same score.\n";

    double score{};
    std::cin >> score;
    if( !std::cin )
    {
        std::cout << "Invalid score entered!\n";
    }
    else
    {
        // find all that have that score
        std::vector<pType::const_iterator> matches;
        for( auto i{ ranks.cbegin() }; i != ranks.cend(); ++i )
        {
            if( i->second == score )
            {
                matches.push_back( i );
            }
        }

        // see if no match
        if( matches.empty() )
        {
            std::cout << "No matching names with a score of " << score << ".\n";
        }
        else
        {
            for( auto i : matches )
            {
                std::cout << std::format("Name: {}\tScore: {}", i->first, i->second) << std::endl;
            }
        }
    }

    keep_window_open();
    return 0;
}
