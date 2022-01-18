#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>


const std::vector<std::pair<char, int>> look_up{
	{'I',1},
	{'V',5},
	{'X',10},
	{'L',50},
	{'C',100},
	{'D',500},
	{'M',1000}
};

class Roman_int
{
public:
	Roman_int() : roman_str{}, roman_int{} {}
	Roman_int(const std::string rn);
	Roman_int(const char* rn);
	Roman_int(const char rn);
	Roman_int(int rn);

	int as_int() const;
	std::string as_str() const;

	// Overloaded cast operators
	operator int() const { return roman_int; }
	operator std::string() const { return roman_str; }

	bool romanToDecimal(const std::string& symbols);
	bool decimalToRoman(int rn_int);

private:
	std::string roman_str;
	int roman_int;

	template<typename T>
	auto find(const std::vector<std::pair<char, int>>& v, T x);
};

// template for some input stream overloads
// -----------------------------------------------------------------------------------
template<typename T>
inline T& operator>>(T& in, Roman_int& r)
{
	in.exceptions(in.exceptions() | std::ios::badbit);
	char c{};
	c = static_cast<char>(in.peek());
	if(std::isdigit(c)){
		int int_str{};
		in >> int_str;
		if(!in.good()){
			return in;
		}
		Roman_int rn{int_str};
		if(rn.as_str().empty()){
			in.clear(std::ios_base::failbit);
			return in;
		}
		r = rn;
	} else{
		std::string str_rn;
		in >> str_rn;
		if(!in.good()){
			return in;
		}
		Roman_int rn{str_rn};
		if(0 == rn.as_int()){
			in.clear(std::ios_base::failbit);
			return in;
		}
		r = rn;
	}
	return in;
}

// template for output stream overloads
// -----------------------------------------------------------------------------------
template<typename T>
inline T& operator<<(T& out, const Roman_int& r)
{
	out << r.as_str();
	return out;
}

 // template for find
 // used to help covert Roman_int from integer to string and string to integer
 // -----------------------------------------------------------------------------------
template<typename T>
inline auto Roman_int::find(const std::vector<std::pair<char, int>>& v, T x)
{
	static_assert(std::is_same<T, char>::value ||
		std::is_same<T, int>::value,
		"unrecognized compare type in Roman_int class");
	auto i{v.begin()};
	if(typeid(char) == typeid(x)){
		for(; i < v.end(); ++i){
			if(i->first == x)return i;
		}
	}
	if(typeid(int) == typeid(x)){
		for(; i < v.end(); ++i){
			if(i->second == x)return i;
		}
	}
	return i;
}
