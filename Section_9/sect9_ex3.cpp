/*
	Written by Jtaim
	Date 18 Jan 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 9 Exercise 3
	Design and implement a Name_pairs class (name,age) pairs.
	- name is a vector<string>
	- age is a vector<double>
	- read_names() to read in a series of names
	- read_ages() to prompt user for an age for each name
	- operator<< to print name[i], age[i] pairs. One per line in the order determined by the name vector.
	- sort() to sort name vector is alphabetical order and reorganizes age vector to match.
	- operator==
	- operator!=

	Implement all operations as members functions.
	Test the class.
*/

#include"../includes/ppp.h"

class Name_pairs
{
public:
	Name_pairs();
	void read_names();
	void read_ages();
	void sort();
	friend std::ostream& operator<<(std::ostream& os, const Name_pairs& np);
	friend bool operator==(const Name_pairs& np1, const Name_pairs& np2);
	friend bool operator!=(const Name_pairs& np1, const Name_pairs& np2);

private:
	std::vector<std::string> m_names;
	std::vector<double> m_ages;
};

Name_pairs::Name_pairs()
{}

void Name_pairs::read_names()
{
	std::cout << "Enter names separated by ',' or new line. EOF (ctrl z) to exit.\n";
	char c{};
	std::string name;
	while(std::cin.get(c)){
		if(c != ',' && c != '\n'){
			if(!name.empty()){
				name += c;
			} else if(c != ' '){
				name += c;
			}
		} else if(!name.empty()){
			m_names.push_back(name);
			name.clear();
		}
	}
	if(std::cin.eof()){
		std::cin.clear();   // clear EOF
	}
}

void Name_pairs::read_ages()
{
	for(auto n : m_names){
		std::cout << "Enter age for " << n << ": ";
		double age{};
		for(;;){
			if(!(std::cin >> age)){
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			} else{
				char c{};
				std::cin.get(c);
				// when entering numbers '\n' is left in the buffer.
				// cin will take the first valid number leaving rest in the stream
				// so added check that nothing left after number other than new line.
				if(c != '\n'){
					std::cin.ignore(std::numeric_limits<int>::max(), '\n');
				} else{
					m_ages.push_back(age);
					break;
				}
			}
			std::cout << "Invalid age entered!\nRenter age for " << n << ": ";
		}
	}
}

void Name_pairs::sort()
{
	using it_size = std::vector<std::string>::size_type;

	std::vector<std::string> copy_names = m_names;
	std::vector<double> copy_ages = m_ages;

	std::stable_sort(m_names.begin(), m_names.end());

	if(m_names.size() == m_ages.size()){
		for(it_size i{}; i < m_names.size(); ++i){
			const auto itr = std::find(copy_names.begin(), copy_names.end(), m_names.at(i));
			if(itr == copy_names.cend()) ppp::error("Name not found!");

			it_size index = static_cast<it_size>(itr - copy_names.begin());
			m_ages.at(i) = copy_ages.at(index);
		}
	} else{
		ppp::error("vector sizes do not match!");
	}
}

std::ostream& operator<<(std::ostream& os, const Name_pairs& np)
{
	// Since operator<< is a friend of the Name_pairs class, we can access Name_pairs members directly.
	if(np.m_names.size() == np.m_ages.size()){
		for(auto itr{np.m_names.begin()}; itr < np.m_names.cend(); ++itr){
			std::size_t index = static_cast<std::size_t>(itr - np.m_names.begin());
			os << np.m_names.at(index) << " is " << np.m_ages.at(index) << " years old.\n";
		}
	} else{
		ppp::error("vector sizes do not match!");
	}
	return os;
}

bool operator==(const Name_pairs& np1, const Name_pairs& np2)
{
	return np1.m_names == np2.m_names && np1.m_ages == np2.m_ages;
}

bool operator!=(const Name_pairs& np1, const Name_pairs& np2)
{
	return !(np1 == np2);
}


int main()
try{
	Name_pairs np;
	np.read_names();
	np.read_ages();
	Name_pairs copy_np{np};

	if(np == copy_np){
		std::cout << "np == copy_np\n";
	} else if(np != copy_np){
		std::cout << "np != copy_np\n";
	}
	std::cout << "np:\n" << np << "\n";
	std::cout << "copy_np:\n" << copy_np << "\n";

	np.sort();
	if(np == copy_np){
		std::cout << "np == copy_np\n";
	} else if(np != copy_np){
		std::cout << "np != copy_np\n";
	}
	std::cout << "np:\n" << np << "\n";
	std::cout << "copy_np:\n" << copy_np << "\n";

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