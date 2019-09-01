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
	using pType = std::pair<std::string, double>;
	pType name_score;
	std::vector<pType> ranks{{"Moe",1}, {"Larry",3}, {"Curly", 3},{"Shemp",4}};

	std::cout << "Enter a score and see all that have same score.\n";

	double score{};
	if(std::cin >> score){
		// find all that have that score
		std::vector<std::vector<pType>::iterator> itrs;
		for(auto itr = ranks.begin(); itr < ranks.end(); ++itr){
			if(itr->second == score){
				itrs.push_back(itr);
			}
		}
		// see if no match
		if(!itrs.empty()){
			for(auto itr : itrs){
				std::cout << "Name: " << itr->first << "\tScore: " << itr->second << std::endl;
			}
		} else{
			std::cout << "No matching names with a score of " << score << ".\n";
		}
	} else{
		std::cout << "Invalid score entered!\n";
	}

	keep_window_open();
	return 0;
}
