//written by James Weiland
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

#include "std_lib_facilities.h" 							// custom header

int main()
{
	uint64_t grains = 0;
	uint64_t new_grains = 0;
	int stop = 64;
	for(int squares=1 ; squares<=stop; squares++) {
		new_grains==0 ? new_grains++ : new_grains*=2;		//ternary operation to deal with first iteration
		//cout << new_grains << '\n';
		grains = grains + new_grains;
		cout << squares << " squares will give " << grains << " grains.\n";
	}
return 0;
}