/*
	Written by Jtaim
	Date 7 Jan 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 8 Exercise 11
	- find smallest and largest element of a vector.
	- compute the mean and median.
	- return a struct of values.
*/

#include"../includes/ppp.h"

template <typename T>
struct slmm_struct
{
	T small{};
	T large{};
	T mean{};
	T median{};
};

template <typename T>
slmm_struct<T> slmm(const std::vector<T>& v)
{
	constexpr bool check =
		std::is_floating_point<T>::value ||
		std::is_same<short, T>::value ||
		std::is_same<unsigned short, T>::value ||
		std::is_same<int, T>::value ||
		std::is_same<unsigned int, T>::value ||
		std::is_same<long, T>::value ||
		std::is_same<unsigned long, T>::value ||
		std::is_same<long long, T>::value ||
		std::is_same<unsigned long long, T>::value;
	static_assert(check, "Vector must be of numeric type");

	if(v.empty()){
		ppp::error("Vector is empty!");
	}
	slmm_struct<T> a{};

	if constexpr(check)
	{
		a.small = a.large = v.front();
		for(auto elem : v){
			if(a.large < elem){
				a.large = elem;
			}
			if(a.small > elem){
				a.small = elem;
			}
			a.mean += elem;
		}
		a.mean /= ppp::narrow_cast<T>(v.size());
		auto v_copy{v};
		// If n is odd then Median (M) = value of ((n + 1)/2)th item term.
		// If n is even then Median (M) = value of [((n)/2)th item term + ((n)/2 + 1)th item term ]/2
		sort(v_copy.begin(), v_copy.end());	// sort numbers
		if((v_copy.size() % 2) > 0){
			a.median = v_copy.at(v_copy.size() / 2);
		} else{
			// if have even amount, remember vector index starts at zero
			// get 2 middle indexes and divide by 2
			a.median = (v_copy.at(v_copy.size() / 2 - 1) + v_copy.at(v_copy.size() / 2)) / 2;
		}
	}
	return a;
}

int main()
try{
	std::vector<double> dprice{3.99, 4.5, 3.45, 5.01, 6.23, 0.99};
	auto d = slmm(dprice);
	std::cout << "Largest price: " << d.large << std::endl;
	std::cout << "Smallest price: " << d.small << std::endl;
	std::cout << "Mean price: " << d.mean << std::endl;
	std::cout << "Median price: " << d.median << std::endl;
	std::cout << "\n\n";

	std::vector<int> nprice{3, 4, 2, 5, 6, 1};
	auto n = slmm(nprice);
	std::cout << "Largest price: " << n.large << std::endl;
	std::cout << "Smallest price: " << n.small << std::endl;
	std::cout << "Mean price: " << n.mean << std::endl;
	std::cout << "Median price: " << n.median << std::endl;

	/*std::vector<std::string> sv{"a", "g"};
	auto s = slmm(sv);*/

	/*std::vector<char> cv{'a', 'f'};
	auto c = slmm(cv);*/

	ppp::keep_window_open();
	return 0;
}
catch(std::exception& e){
	std::cerr << "exception: " << e.what() << std::endl;
	ppp::keep_window_open();
	return 1;
}
catch(...){
	std::cerr << "exception\n";
	ppp::keep_window_open();
	return 2;
}