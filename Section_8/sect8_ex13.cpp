/*
	Written by Jtaim
	Date 12 Jan 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 8 Exercise 13
	- Write a function with input vector<string> argument.
	- returns a vector<int> containing the number of characters in each string.
	- also find the longest and shortest string.
	- lexicographically first and last string

	keep as one function and separate function?
	I guess depends on the situation but keeping 3 separate functions helps keeps each specialized.
	Could also just find size of each to find shortest and longest word.
	also for the lexicographically first and last string could use the sort function from the STL algorithm library
*/

#include"../includes/ppp.h"

template<typename T>
void print_vector(const std::vector<T>& v)
{
	if(!v.empty()){
		for(const auto& element : v){
			std::cout << element << '\n';
		}
		std::cout << '\n';
	} else{
		std::cout << "vector is empty\n";
	}
}

std::vector<int> find_size(const std::vector<std::string>& vs)
{
	std::vector<int> vn;
	if(!vs.empty()){
		for(const auto& s : vs){
			vn.push_back(static_cast<int>(s.size()));
		}
	}
	return vn;
}

int main()
{
	std::vector<std::string> vs{"one hundred", "zero", "one", "five thousand", "two", "zero", "three", "four"};
	//std::vector<std::string> vs;

	auto sizes = find_size(vs);
	print_vector(sizes);

	auto lengths = vs;
	std::stable_sort(lengths.begin(), lengths.end(), [](const std::string& a, const std::string& b){return a.size() < b.size(); });
	print_vector(lengths);

	auto alpha_order = vs;
	std::stable_sort(alpha_order.begin(), alpha_order.end());
	print_vector(alpha_order);

	ppp::keep_window_open();
	return 0;
}