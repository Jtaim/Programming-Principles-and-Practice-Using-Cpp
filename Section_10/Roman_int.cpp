#include "Roman_int.h"

Roman_int::Roman_int(std::string rn)
	: roman_str(rn), roman_int(0)
{
	roman_int = romanToDecimal(roman_str);
	if(0 == roman_int) roman_str = "";
}

int Roman_int::as_int() const
{
	return roman_int;
}

std::string Roman_int::getRomanNumerial() const
{
	return roman_str;
}

// Returns decimal value of roman numeral
// Return 0 indicates malformed roman numeral
int Roman_int::romanToDecimal(const std::string& str) const
{
	int res{};
	// Traverse given input
	for(auto i{str.cbegin()}; i != str.cend(); ++i){
		// Getting value of symbol 
		auto s1 = look_up.find(*i);
		if(s1 != look_up.cend()){
			const auto next{i + 1};
			if((next) != str.cend()){
				// Getting next value of symbol 
				auto s2 = look_up.find(*next);
				if(s2 != look_up.cend()){
				// Comparing both values 
					if(s1->second >= s2->second){
						// Value of current symbol is greater 
						// or equal to the next symbol 
						res += s1->second;
					}
					else{
						// Value of current symbol is 
						// less than the next symbol 
						res += (s2->second - s1->second);
						++i; // used current and next symbol
					}
				}
				else{
					// unrecognized symbol found
					return 0;
				}
			}
			else{
				// just used current symbol
				res += s1->second;
			}
		}
		else{
			// unrecognized symbol found
			return 0;
		}
	}
	return res;
}
