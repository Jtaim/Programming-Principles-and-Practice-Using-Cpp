#include "Money.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

Money::Money(std::string m)
{
	if(m.empty()){
		m_cents = 0;
	} else{
		std::stringstream ss{m};
		char c{};
		std::string temp_str;
		for(ss.get(c); !std::isdigit(c) && c != '.'; ss.get(c)){
			temp_str += c;
		}
		ss.putback(c); // putback last that tested as digit or .

		auto itr = std::find_if(currencyInfo.begin(), currencyInfo.end(),
			[temp_str](currencyInfoTuple cit){return std::get<1>(cit) == temp_str; });
		if(itr == currencyInfo.cend()){
			itr = std::find_if(currencyInfo.begin(), currencyInfo.end(),
				[temp_str](currencyInfoTuple cit){return std::get<0>(cit) == temp_str; });
			if(itr == currencyInfo.cend()){
				throw std::invalid_argument("expected currency symbol");
			}
		}
		m_currencyCode = std::get<0>(*itr);
		m_currencySign = std::get<1>(*itr);

		double amount{};
		if(!(ss >> amount)){
			throw std::invalid_argument("expected monitory amount");
		} else if(!ss.eof()){
			throw std::invalid_argument("Data left in the Money class constructor stream");
		} else if(amount > 0.004){
			m_cents = static_cast<long>(amount * 100);
			if((amount * 100 - m_cents) > 0.4){
				++m_cents;
			}
		} else{
			m_cents = 0;
		}
	}
}

std::string Money::get_cents()
{
	std::stringstream ss;
	ss << m_currencySign << std::fixed << std::setprecision(2) << static_cast<double>(m_cents / 100.0);
	return ss.str();
}
