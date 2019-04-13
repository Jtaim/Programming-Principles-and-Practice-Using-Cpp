#include "Roman_int.h"

Roman_int::Roman_int(const std::string rn)
	: roman_str{rn}, roman_int{}
{
	if(!romanToDecimal(roman_str)){
		roman_str = "";
	}
}

Roman_int::Roman_int(const char* rn)
	: roman_str{rn}, roman_int{}
{
	if(!romanToDecimal(roman_str)){
		roman_str = "";
	}
}

Roman_int::Roman_int(const char rn)
	: roman_str{rn}, roman_int{}
{
	if(!romanToDecimal(roman_str)){
		roman_str = "";
	}
}

Roman_int::Roman_int(int rn)
	: roman_str{}, roman_int{rn}
{
	if(roman_int > 3999) throw std::runtime_error("Sorry not sure how to deal with large numbers over 3999");
	if(!decimalToRoman(roman_int)){
		roman_int = 0;
	}
}

int Roman_int::as_int() const
{
	return roman_int;
}

std::string Roman_int::as_str() const
{
	return roman_str;
}

// parse string to decimal value of roman numeral
// Return true indicates valid roman numeral
// Return false indicates malformed roman numeral
bool Roman_int::romanToDecimal(const std::string& symbols)
{
	roman_int = 0;
	// Traverse given input
	for(auto symbol_itr{symbols.cbegin()}; symbol_itr != symbols.cend(); ++symbol_itr){
		// Getting value of symbol 
		auto symbol_value = find(look_up, *symbol_itr);
		if(symbol_value == look_up.cend()){
			return false; // unrecognized symbol found
		}
		auto next_symbol_itr{symbol_itr + 1};
		if((next_symbol_itr) != symbols.cend()){
			auto next_symbol_value = find(look_up, *next_symbol_itr);
			if(next_symbol_value == look_up.cend()){
				return false; // unrecognized symbol found
			}
			if(symbol_value->second >= next_symbol_value->second){
				roman_int += symbol_value->second;
			}
			else{
				roman_int += (next_symbol_value->second - symbol_value->second);
				++symbol_itr; // used current and next symbol value
			}
		}
		else{
			// just used current symbol
			roman_int += symbol_value->second;
		}
	}
	// parsed a good number
	return true;
}

// parse decimal to string value of roman numeral
// Return true indicates valid roman numeral
// Return false indicates malformed roman numeral
bool Roman_int::decimalToRoman(int rn_int)
{
	roman_str = "";
	if(0 >= rn_int) return false;
	auto int_str{std::to_string(rn_int)};
	int multiplier{1}; // start with ones digit
	for(auto c{int_str.rbegin()}; c < int_str.crend(); ++c){
		int convert{*c - '0'}; //convert to correct number (ASCII '0' = 48)
		if(convert){
			switch(convert){
				case 1: case 2: case 3:
					for(int i{}; i < convert; ++i){
						roman_str.insert(roman_str.begin(), find(look_up, multiplier)->first);
					}
					break;
				case 4:
					roman_str.insert(roman_str.begin(), find(look_up, multiplier)->first);
					roman_str.insert(roman_str.begin() + 1, find(look_up, 5 * multiplier)->first);
					break;
				case 5:
					roman_str.insert(roman_str.begin(), find(look_up, 5 * multiplier)->first);
					break;
				case 6: case 7: case 8:
					roman_str.insert(roman_str.begin(), find(look_up, 5 * multiplier)->first);
					for(int i{}; i < convert - 5; ++i){
						roman_str.insert(roman_str.begin() + 1, find(look_up, multiplier)->first);
					}
					break;
				case 9:
					roman_str.insert(roman_str.begin(), find(look_up, multiplier)->first);
					roman_str.insert(roman_str.begin() + 1, find(look_up, 10 * multiplier)->first);
					break;
				default:
					return false;
			}
		}
		multiplier *= 10;
	}
	return true;
}
