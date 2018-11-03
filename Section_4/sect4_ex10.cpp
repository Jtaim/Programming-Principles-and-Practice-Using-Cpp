//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 10.
 Write a program that plays the game “Rock, Paper, Scissors.”
 If you are not familiar with the game do some research (e.g., on the web using Google).
 Research is a common task for programmers. Use a switch-statement to solve this exercise.
 Also, the machine should give random answers (i.e., select the next rock, paper, or scissors randomly).
 Real randomness is too hard to provide just now, so just build a vector with a sequence of values to be
 used as “the next value.” If you build the vector into the program, it will always play the same game,
 so maybe you should let the user enter some values.
 Try variations to make it less easy for the user to guess which move the machine will make next.
*/

#include "section4.h"

unsigned ran_num(int);

int main()
{
    using std::cout;
    using std::cin;

    const std::vector<std::string> rps{ "ROCK","PAPER","SCISSORS" };

    auto play_again{ '?' };
    auto pselect{ 0U };
    auto cselect{ 0U };
    do {
        cout << "Select (1) for Rock (2) for Paper (3) for Scissors\n";
        // check for proper input
        if (!(cin >> pselect) || pselect > 3) {
            simple_error("selected r/p/s poorly\n");
        }
        cselect = ran_num(3);  //have only 3 selections gets random selection between 1 and 3
        cout << "Your selection was " << rps.at(pselect - 1) << " the computer selected "
            << rps.at(cselect - 1) << '\n';
        cout << "Would you like to play again (y or n)\n";
        cin >> play_again;
        // check for proper input
        if (play_again != 'y' && play_again != 'n') {
            simple_error("selected y/n poorly\n");
        }
        cout << "\n\n";
    } while (play_again == 'y');
    keep_window_open();
    return 0;
}

// function to generate random number
unsigned ran_num(int nHigh)
{
    std::srand(std::time(0)); // set initial seed value to system clock
    return (std::rand() % nHigh + 1);
    //(rand() % (nHigh - nLow + 1)) + nLow;  //if want low number something other than 1
}
