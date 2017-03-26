//written by Jtaim
//date 26 Mar 2017
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

#include "section4.h"	//custom header

int main()
{
	using namespace std;
	//list of disliked words
	const vector<string> disliked{ "you", "i", "me" };

	vector<string> words;
	// read whitespace-separated words
	for (string word; cin >> word; ) {
		for (auto& c : word) {
			c = static_cast<char>(tolower(c));
		}
		for (string str : disliked) {
			if (str == word) { word = "BLEEP"; }
		}
		words.push_back(word);	// put into vector
	}
	cout << "Number of words: " << words.size() << endl;
	for (auto str : words) {
		cout << str << endl;
	}
	keep_window_open();
	return 0;
}
