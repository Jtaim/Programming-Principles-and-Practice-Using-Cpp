/*
std_lib_facilities.h
*/

/*
simple "Programming: Principles and Practice using C++ (second edition)" course header to
be used for the first few weeks.
It provides the most common standard headers (in the global namespace)
and minimal exception/error support.

Students: please don't try to understand the details of headers just yet.
All will be explained. This header is primarily used so that you don't have
to understand every concept all at once.

By Chapter 10, you don't need this file and after Chapter 21, you'll understand it

Revised April 25, 2010: simple_error() added

Revised November 25 2013: remove support for pre-C++11 compilers, use C++11: <chrono>
Revised November 28 2013: add a few container algorithms
Revised June 8 2014: added #ifndef to workaround Microsoft C++11 weakness
*/

#ifndef H112
#define H112 251113L


#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<list>
#include <forward_list>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include <array>
#include <regex>
#include<random>
#include<stdexcept>

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------

typedef long Unicode;

//------------------------------------------------------------------------------

//using namespace std;

template<typename T> std::string to_string(const T& t)
{
	std::ostringstream os;
	os << t;
	return os.str();
}

struct Range_error : std::out_of_range {	// enhanced vector range error reporting
	int index;
	Range_error(int i) :out_of_range("Range error: " + to_string(i)), index(i) { }
};


// trivially range-checked vector (no iterator checking):
template< class t> struct vector : public std::vector<t> {
	using size_type = typename std::vector<t>::size_type;

#ifdef _msc_ver
// microsoft doesn't yet support c++11 inheriting constructors
	vector() { }
	explicit vector(size_type n) :std::vector<t>(n) {}
	vector(size_type n, const t& v) :std::vector<t>(n, v) {}
	template <class i>
	vector(i first, i last) : std::vector<t>(first, last) {}
	vector(initializer_list<t> list) : std::vector<t>(list) {}
#else
	using std::vector<t>::vector;	// inheriting constructor
#endif

	t& operator[](unsigned int i) // rather than return at(i);
	{
		if (i<0 || this->size() <= i) throw range_error(i);
		return std::vector<t>::operator[](i);
	}
	const t& operator[](unsigned int i) const
	{
		if (i<0 || this->size() <= i) throw range_error(i);
		return std::vector<t>::operator[](i);
	}
};

// disgusting macro hack to get a range checked vector:
#define vector vector

// trivially range-checked string (no iterator checking):
struct string : std::string {
	using size_type = std::string::size_type;
	//using string::string;

	char& operator[](unsigned int i) // rather than return at(i);
	{
		if (i<0 || size() <= i) throw std::range_error(i);
		return std::string::operator[](i);
	}

	const char& operator[](unsigned int i) const
	{
		if (i<0 || size() <= i) throw std::range_error(i);
		return std::string::operator[](i);
	}
};


namespace std {

	template<> struct hash<string>
	{
		size_t operator()(const string& s) const
		{
			return hash<std::string>()(s);
		}
	};

} // of namespace std


struct Exit : std::runtime_error {
	Exit() : std::runtime_error("Exit") {}
};

// error() simply disguises throws:
inline void error(const std::string& s)
{
	throw std::runtime_error(s);
}

inline void error(const std::string& s, const std::string& s2)
{
	error(s + s2);
}

inline void error(const std::string& s, int i)
{
	std::ostringstream os;
	os << s << ": " << i;
	error(os.str());
}


template<class T> char* as_bytes(T& i)	// needed for binary I/O
{
	void* addr = &i;	// get the address of the first byte
						// of memory used to store the object
	return static_cast<char*>(addr); // treat that memory as bytes
}


inline void keep_window_open()
{
	std::cin.clear();
	std::cout << "Please enter a character to exit\n";
	char ch;
	std::cin >> ch;
	return;
}

inline void keep_window_open(std::string s)
{
	if (s == "") return;
	std::cin.clear();
	std::cin.ignore(120, '\n');
	for (;;) {
		std::cout << "Please enter " << s << " to exit\n";
		std::string ss;
		while (std::cin >> ss && ss != s)
			std::cout << "Please enter " << s << " to exit\n";
		return;
	}
}



// error function to be used (only) until error() is introduced in Chapter 5:
inline void simple_error(std::string s)	// write ``error: s and exit program
{
	std::cerr << "error: " << s << '\n';
	keep_window_open();		// for some Windows environments
	exit(1);
}

// make std::min() and std::max() accessible on systems with antisocial macros:
#undef min
#undef max


// run-time checked narrowing cast (type conversion). See ???.
template<typename R, typename A> R narrow_cast(const A& a)
{
	R r = R(a);
	if (A(r) != a) error(string("info loss"));
	return r;
}

// random number generators. See 24.7.



inline int randint(int min, int max) { static std::default_random_engine ran; return std::uniform_int_distribution<>{min, max}(ran); }

inline int randint(int max) { return randint(0, max); }

//inline double sqrt(int x) { return sqrt(double(x)); }	// to match C++0x

// container algorithms. See 21.9.

template<typename C>
using Value_type = typename C::value_type;

template<typename C>
using Iterator = typename C::iterator;

template<typename C>
// requires Container<C>()
void sort(C& c)
{
	std::sort(c.begin(), c.end());
}

template<typename C, typename Pred>
// requires Container<C>() && Binary_Predicate<Value_type<C>>()
void sort(C& c, Pred p)
{
	std::sort(c.begin(), c.end(), p);
}

template<typename C, typename Val>
// requires Container<C>() && Equality_comparable<C,Val>()
Iterator<C> find(C& c, Val v)
{
	return std::find(c.begin(), c.end(), v);
}

template<typename C, typename Pred>
// requires Container<C>() && Predicate<Pred,Value_type<C>>()
Iterator<C> find_if(C& c, Pred p)
{
	return std::find_if(c.begin(), c.end(), p);
}

#endif //H112
