#include "Roman_int.h"

Roman_int::Roman_int(std::string rn)
	: roman_str(rn), roman_int(not_roman)
{
	roman_int = romanToDecimal(roman_str);
}

int Roman_int::as_int() const
{
	return roman_int;
}

std::string Roman_int::getRomanNumerial() const
{
	return roman_str;
}

int value(const char r)
{
	switch(r){
		case 'I':
			return 1;
		case 'V':
			return 5;
		case 'X':
			return 10;
		case 'L':
			return 50;
		case 'C':
			return 100;
		case 'D':
			return 500;
		case 'M':
			return 1000;
		default:
			return not_roman;
	}
}

// Returns decimal value of roman numeral
int Roman_int::romanToDecimal(const std::string& str)
{
	if(str.empty()) return not_roman;
	// Initialize result 
	int res{};
	// Traverse given input 
	for(std::string::size_type i{}; i < str.size(); ++i){
		// Getting value of symbol s[i] 
		int s1{value(str.at(i))};
		if(not_roman == s1) return not_roman;

		if(i + 1 < str.size()){
			// Getting value of symbol s[i+1] 
			int s2{value(str.at(i + 1))};
			if(not_roman == s2) return not_roman;

			// Comparing both values 
			if(s1 >= s2){
				// Value of current symbol is greater 
				// or equal to the next symbol 
				res = res + s1;
			}
			else{
				res = res + s2 - s1;
				++i; // Value of current symbol is 
					 // less than the next symbol 
			}
		}
		else{
			res = res + s1;
			++i;
		}
	}
	return res;
}
