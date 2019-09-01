//written by Jtaim
//date 8 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 14
read (day-of-the-week,value) pairs, collect values for each day in a separate vector.
Ignore illegal days, but accept common synonyms.
escape by "q 5" for day value entry
Print sum and list of values for each day when there is no more input
count of and output rejected entries.
*/

#include "section5.h"

using pType = std::pair <std::vector<std::string>, std::vector<int>>;
using vType = std::vector<pType>;
using numType = pType::second_type::value_type;

numType add(numType n1, numType n2)
{
	if(((n2 > 0) && (n1 > (std::numeric_limits< numType>::max() - n2))) ||
		((n2 < 0) && (n1 < (std::numeric_limits< numType>::min() - n2)))){
		error("overflow error");
	}
	return n1 + n2;
}

int main()
try{
	const std::string termination{"q"};

	vType weekdays{
	{ {"sun","sunday"   }, {} },
	{ {"mon","monday"   }, {} },
	{ {"tue","tuesday"  }, {} },
	{ {"wed","wednesday"}, {} },
	{ {"thu","thursday" }, {} },
	{ {"fri","friday"   }, {} },
	{ {"sat","saturday" }, {} }
	};

	unsigned rejects{};
	std::cout << "Enter days of the week (ex:Mon or Monday) and a value. Enter q to exit\n";
	while(true){
		std::string day;
		std::cin >> day;
		for(auto& c : day){
			c = narrow_cast<char>(tolower(c));
		}
		// check for matching day
		auto validDay{weekdays.begin()};
		for(; validDay < weekdays.end(); ++validDay){
			bool found{false};
			for(auto d : validDay->first){
				if(d == day){
					found = true;
					break;
				}
			}
			if(found){
				break;
			}
		}
		// day not found, check if valid termination
		if(validDay == weekdays.end()){
			if(day == termination){
				// stop while loop
				break;
			}
			++rejects;
		}
		// valid day now look for number value
		else{
			numType value{};
			if(!(std::cin >> value)){
				std::cin.clear();
				// check if input number was overflowed
				if(value == std::numeric_limits<numType>::max() ||
					value == std::numeric_limits<numType>::min()){
					error("Entered number overflowed number type!");
				}
				++rejects;
			} else{
				validDay->second.push_back(value);
			}
		}
	}

	//print the results
	std::cout << std::endl;
	for(auto d : weekdays){
		numType sum{};
		for(auto num : d.second){
			sum = add(sum, num);
		}
		std::cout << std::left << std::setfill('.') << std::setw(20) << d.first.at(1) << " " << sum << '\n';
	}
	std::cout << "\n\n" << std::left << std::setfill('.') << std::setw(20) << "rejects" << " " << rejects << std::endl;

	keep_window_open();
	return 0;
}
catch(std::exception& e){
	std::cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch(...){
	std::cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}
