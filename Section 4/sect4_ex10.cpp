//written by Jtaim
//date 8 Oct 2015
//update 17 Dec 2016
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
#include <vector>
#include <ctime>

unsigned int ran_num(int);

int main()
{
	using std::cout;
	using std::cin;

	const std::vector<std::string> RPS{ "ROCK","PAPER","SCISSORS" };
	
	char play_again = 'y';
	unsigned pselect = 1;
	unsigned cselect = 1;
	do
	{
		cout << "Select (1) for Rock (2) for Paper (3) for Scissors ";
		while (cin >> pselect)  // check for proper input
		{
			if (pselect >= 1 && pselect <= 3)
				break;
			else
				cout << "You did not make the proper selection. Try again ";
		}
		cselect = ran_num(3);  //have only 3 selections gets random selection between 1 and 3
		cout << "Your selection was " << RPS.at(pselect - 1) << " the computer selected " << RPS.at(cselect - 1) << '\n';  // -1 to get proper index
		cout << "Would you like to play again (y or n) ";
		while (cin >> play_again)
		{
			if (play_again == 'y' || play_again == 'n')
				break;
			else
				cout << "You did not make the proper selection. Try again ";
		}
		cout << "\n\n\n";
	} while (play_again == 'y');
	keep_window_open();
	return 0;
}

// function to generate random number
unsigned int ran_num(int nHigh)
{
	std::srand(std::time(0)); // set initial seed value to system clock
	return (std::rand() % nHigh + 1);
	//(rand() % (nHigh - nLow + 1)) + nLow;  //if want low number something other than 1
}
