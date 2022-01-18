#include "Library.h"
#include <iostream>

namespace library
{


	Library::Library()
	{}

	void Library::add_book()
	{
		std::cout << "Enter ISBN:\n";
		std::string isbn{get_string()};

		std::cout << "Enter title:\n";
		std::string title{get_string()};

		std::cout << "Enter author:\n";
		std::string author{get_string()};

		std::cout << "Enter copyright year:\n";
		int copyright{};
		std::cin >> copyright;

		// TODO get genre
		if(!std::cin.good() || isbn.empty() || title.empty() || author.empty()){
			throw std::runtime_error("Invalid Library class Book created");
		}

		m_books.push_back(Book(isbn, title, author, copyright));
	}

	void Library::add_patron()
	{
		std::string name{get_string()};
		if(!name.empty()){
			int card_number{};
			if(!m_patrons.empty()){
				for(auto p : m_patrons){
					auto pcn = p.get_card_number();
					if(pcn >= card_number){
						card_number = pcn + 1;
					}
				}
			} else{
				card_number = 1;
			}
			if(!name.empty() && card_number != 0){
				Patron patron(name, card_number);
				std::cout << "Set any fees:\n";
				double fees{};
				std::cin >> fees;
				patron.set_fees(fees);
				m_patrons.push_back(patron);
				//std::cout << patron << '\n';
			} else{
				throw std::runtime_error("Invalid Library class Patron created");
			}
		} else{
			throw std::runtime_error("Invalid Library class Patron name created");
		}
	}

	// make sure patron and book is part of library 
	// if either is not part of library report an error
	// if user owes fees report an error
	// if no error create a transaction to place into transactions vector
	void Library::check_out_book(Book& b, Patron& p)
	{
		auto b_itr{std::find(m_books.begin(), m_books.end(), b)};
		if(b_itr == m_books.cend()){
			throw std::runtime_error("Library does not have this book");
		}
		if(b_itr->is_checked_out()){
			throw std::runtime_error("Book is checked out");
		}

		auto p_itr{std::find(m_patrons.begin(), m_patrons.end(), p)};
		if(p_itr == m_patrons.cend()){
			throw std::runtime_error("User is not registered");
		}
		if(p_itr->is_outstanding_fee()){
			throw std::runtime_error("User has outstanding fees");
		}

		b_itr->check_inout(true);

		// TODO get current date
		transactions.push_back(Transaction(*b_itr, *p_itr, Chrono::Date(2019, Chrono::Month::jan, 21)));
	}

	std::vector <std::pair<std::string, double>> Library::get_outstanding_fees()
	{
		std::vector <std::pair<std::string, double>> list;
		for(auto itr{m_patrons.begin()}; itr < m_patrons.end(); ++itr){
			if(itr->is_outstanding_fee()){
				list.push_back(std::make_pair(itr->get_name(), itr->get_fees()));
			}
		}
		return list;
	}

	std::string Library::get_string()
	{
		std::string s;
		char c{};
		while(std::cin.get(c)){
			if(c == ',' || c == '\n') break;
			else if(!s.empty()) s += c;
			// eat space at beginning of entered string
			else if(s.empty() && c != ' ') s += c;
		}
		if(!std::cin.good() && !std::cin.eof()){
			throw std::runtime_error("Invalid Library class string object");
		}
		std::cin.clear();   // clear EOF
		return s;
	}

}
