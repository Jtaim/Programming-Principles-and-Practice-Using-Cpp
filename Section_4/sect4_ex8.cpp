//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 8.
 There is an old story that the emperor wanted to thank the inventor of the game of chess and asked the inventor to
 name his reward. The inventor asked for one grain of rice for the first square, 2 for the second, 4 for the third,
 and so on, doubling for each of the 64 squares. That may sound modest, but there wasn’t that much rice in the empire!
 Write a program to calculate how many squares are required to give the inventor at least 1000 grains of rice,
 at least 1,000,000 grains, and at least 1,000,000,000 grains.
 You’ll need a loop, of course, and probably an int to keep track of which square you are at,
 an int to keep the number of grains on the current square, and an int to keep track of the grains on all previous squares.
 We suggest that you write out the value of all your variables for each iteration of the loop so that you can see what’s going on.
*/

#include "section4.h"

int main()
{
    using std::cout;

    constexpr auto maxSquares{ 64 };

    auto current_square_grains{ 0ULL };
    auto previous_square_grains{ 0ULL };
    for (auto square = 0; square < maxSquares; square++) {
        //powers of 2 will provide double of previous number 2^0=1, 2^1=2, 2^2=4 2^3=8 ...
        current_square_grains = static_cast<decltype(current_square_grains)>(std::pow(2, square));
        //cout << "square " << square + 1 << " has " << current_square_grains << " grains.\n";
        //cout << "Sum of the previous squares is " << previous_square_grains << " grains.\n\n";
        //add them up
        previous_square_grains += current_square_grains;
        if (current_square_grains <= 1000 && previous_square_grains >= 1000) {
            cout << square + 1 << " provides approximately 1000 grains.\n\n";
        }
        else if (current_square_grains <= 1000000 && previous_square_grains >= 1000000) {
            cout << square + 1 << " provides approximately 1,000,000 grains.\n\n";
        }
        else if (current_square_grains <= 1000000000 && previous_square_grains >= 1000000000) {
            cout << square + 1 << " provides approximately 1,000,000,000 grains.\n\n";
        }
        else {
            continue;
        }
    }
    keep_window_open();
    return 0;
}
