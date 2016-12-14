//written by Jtaim
//date 22 Sept 2015
//updated 4 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Try This 4.6.4
Write a program that “bleeps” out words that you don’t like; that is, 
you read in words using cin and print them again on cout. 
If a word is among a few you have defined, you write out BLEEP instead of that word. 
Start with one “disliked word” such as
string disliked = “Broccoli”;
When that works, add a few more.
*/

#include <vector>
#include "section4.h" //custom header

int main()
{
	using namespace std;
	const vector<string> disliked{ "you", "I", "me" };	//list of disliked words
	vector<string> words;
	for (string word; cin >> word; )// read whitespace-separated words
	{
		words.push_back(word);		// put into vector
	}
	cin.clear();					// clear EOF (ctrl-z) flag so next cin will accept data
	cout << "Number of words: " << words.size() << endl;
	for (unsigned int i = 0; i < words.size(); ++i)
	{
		for (string word : disliked)
		{
			if (word == words[i])
				words[i] = "BLEEP";
		}
		cout << words[i] << endl;
	}
	keep_window_open();
	return 0;
}
