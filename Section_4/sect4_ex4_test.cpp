//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition
/*
Section 4 exercise 4 debug is to try all iterations of possible guesses.
A program to play a numbers guessing game.
The user thinks of a number between 1 and 100 and your program asks questions to figure out what the number is
(e.g., "Is the number you are thinking of less than 50?").
Your program should be able to identify the number after asking no more than seven questions.
Hint: Use the < and <= operators and the if-else construct.
*/

#include "section4.h"

int main()
{
    int constexpr maxRange = 100;       // maximum number can select
    int constexpr minRange = 1;         // minimum number can guess
    int constexpr maxGuessAttempts = 7; // maximum number of times to ask before identifying the number

    // for loop to debug all combinations
    for (auto iteration = minRange; iteration <= maxRange; iteration++) {

        int high = maxRange; 					// keeps track of a new high
        int low = minRange;						// keeps track of a new low
        int guess = (high - low) / 2 + low;     // keeps track of the next guess
        int guessAttempts = 0;					// keeps count of guess count

        //std::cout << "Pick a number between " << low << " and " << high << " and let me try to guess it by asking some questions.\n";

        bool isFound = false;
        while (!isFound && guessAttempts < maxGuessAttempts) {
            //std::cout << "Is your number <= " << guess << " (y or n)? ";
            char yesOrNo = ' ';

            //********************************************************************************************
            iteration <= guess ? yesOrNo = 'y' : yesOrNo = 'n';
            std::cin.putback(yesOrNo);
            //std::cout << "Is " << iteration << " <= " << guess << " " << choice << '\n';
            //********************************************************************************************

            std::cin >> yesOrNo;
            if (yesOrNo == 'y' || yesOrNo == 'n') {
                guessAttempts++;
                yesOrNo == 'y' ? high = guess : low = guess + 1;
                high == low ? isFound = true : guess = (high - low) / 2 + low;
            }
            else {
                std::cout << "You did not pick a valid (y or n) answer.  Select again.\n";
            }
        }

        if (isFound) {
            std::cout << "Found the answer " << high << " in " << guessAttempts << " guesses.\n";
        }
        else {
            simple_error("Exceeded max number of guesses\n");
        }
    } // need extra bracket to close for loop

    keep_window_open();
    return 0;
}
