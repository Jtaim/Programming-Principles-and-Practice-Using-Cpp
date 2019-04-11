#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

const std::map<char, int> look_up{
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
	Roman_int(std::string rn = " ");

	int as_int() const;
	std::string getRomanNumerial() const;

private:
	std::string roman_str;
	int roman_int;

	int romanToDecimal(const std::string& str) const;
};

// relational operator overloads
inline bool operator==(const Roman_int& lhs, const Roman_int& rhs)
{
	return (lhs.as_int() == rhs.as_int());
}
inline bool operator==(const Roman_int& lhs, const int rhs)
{
	return (lhs.as_int() == rhs);
}
inline bool operator==(const int lhs, const Roman_int& rhs)
{
	return (lhs == rhs.as_int());
}


inline bool operator>(const Roman_int& lhs, const Roman_int& rhs)
{
	return (lhs.as_int() > rhs.as_int());
}
inline bool operator>(const Roman_int& lhs, const int rhs)
{
	return (lhs.as_int() > rhs);
}
inline bool operator>(const int lhs, const Roman_int& rhs)
{
	return (lhs > rhs.as_int());
}

inline bool operator<(const Roman_int& lhs, const Roman_int& rhs)
{
	return (lhs.as_int() < rhs.as_int());
}
inline bool operator<(const Roman_int& lhs, const int rhs)
{
	return (lhs.as_int() < rhs);
}
inline bool operator<(const int lhs, const Roman_int& rhs)
{
	return (lhs < rhs.as_int());
}

template<typename T, typename U>
bool operator!=(const T& lhs, const U& rhs)
{
	return !(lhs == rhs);
}

template<typename T, typename U>
bool operator>=(const T& lhs, const U& rhs)
{
	return !(lhs == rhs || lhs > rhs);
}

template<typename T, typename U>
bool operator<=(const T& lhs, const U& rhs)
{
	return !(lhs == rhs || lhs > rhs);
}

// template for some input stream overloads
// -----------------------------------------------------------------------------------
template<typename T>
T& operator>>(T& in, Roman_int& r)
{
	in.exceptions(in.exceptions() | std::ios::badbit);
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
	return in;
}

// template for output stream overloads
// -----------------------------------------------------------------------------------
template<typename T>
T& operator<<(T& out, const Roman_int& r)
{
	out << r.getRomanNumerial();
	return out;
}