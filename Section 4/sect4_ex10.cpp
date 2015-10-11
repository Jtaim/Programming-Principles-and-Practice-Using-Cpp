//written by Jtaim
//date 8 Oct 2015
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

#include "section4.h"  // custom header

//uses rand() function to generate random number
unsigned int RanNum(int);

int main()
{
	char play_again = 'y';
	unsigned pselect = 1;
	unsigned cselect = 1;
	
	const vector<string> rps {"ROCK","PAPER","SCISSORS"};
		
	do
	{
		cout << "Select (1) for Rock (2) for Paper (3) for Scissors ";
		while(cin>>pselect)  // check for proper input
		{
			if(pselect>=1 && pselect<=3)
				break;
			else
				cout << "You did not make the proper selection. Try again ";
		}
		cselect = RanNum(3);  //have only 3 selections gets random selection between 1 and 3
		cout << "Your selection was " << rps[pselect-1] << " the computer selected " << rps[cselect-1] << '\n';  // -1 to get proper index
		cout << "Would you like to play again (y or n) ";
		while(cin>>play_again)
		{
			if(play_again=='y'||play_again=='n')
				break;
			else
				cout << "You did not make the proper selection. Try again ";
		}
		cout << "\n\n\n";
	} while(play_again == 'y');
	keep_window_open();
	return 0;
}
// function to generate random number
unsigned int RanNum(int nHigh)
{
	srand(time(0)); // set initial seed value to system clock
	return (rand() % nHigh + 1);
	//(rand() % (nHigh - nLow + 1)) + nLow;  //if want low number something otherthan 1
}