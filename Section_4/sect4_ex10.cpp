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

int main()
{
    //Will be used to obtain a seed for the random number engine
    std::random_device rd;
    //Standard mersenne_twister_engine seeded with rd()
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2);

    const std::vector<std::string> rps{ "ROCK", "PAPER", "SCISSORS" };

    bool playAgain{ false };
    do {
        std::cout << "Select (1) for Rock (2) for Paper (3) for Scissors" << std::endl;
        // check for proper input
        int pSelect{ 0 };
        if (!(std::cin >> pSelect) || pSelect > 3) {
            simple_error("selected r/p/s poorly");
        }
        auto cSelect = dis(gen);  //have only 3 selections gets random selection between 0 and 2
        std::cout << "Computer selection = " << cSelect << std::endl;
        std::cout << "Your selection was " << rps.at(pSelect - 1) << " the computer selected "
            << rps.at(cSelect) << std::endl;

        std::cout << "\nWould you like to play again (y or n)" << std::endl;
        char c;
        std::cin >> c;
        // check for proper input
        c == 'y' ? playAgain = true : playAgain = false;
    } while (playAgain);

    keep_window_open();
    return 0;
}
