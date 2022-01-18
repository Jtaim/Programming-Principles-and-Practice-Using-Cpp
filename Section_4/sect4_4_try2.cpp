//written by Jtaim
//date 26 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Try This 4.4.1.3
program that converts yen, euro, pound, yuan, and kroner into dollar
*/

#include "section4.h"

int main()
{
  constexpr auto convertRate = std::to_array<std::pair<std::string_view, long double>>({
    {"yen", 113.21L},
    {"euro", 0.88L},
    {"pound", 0.77L},
    {"danish krone", 6.55L},
    {"yuan", 6.89L}
    });

  std::cout << "Please enter an amount followed by a currency to convert to dollar:\n";
  for (auto i{convertRate.begin()}; i < convertRate.end(); ++i)
  {
    if (i == convertRate.end() - 1)
    {
      std::cout << std::format("or {}\n", i->first);
    }
    else
    {
      std::cout << std::format("{}, ", i->first);
    }
  }

  // get currency amount
  long double amount{};
  if (!(std::cin >> amount))
  {
    simple_error("entered amount unknown");
  }

  // get currency to covert
  std::string currency;
  std::getline(std::cin >> std::ws, currency);

  // change entered currency to lower case
  for (auto& c : currency)
  {
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
  }

  // find conversion type
  auto conversion = std::find_if(convertRate.cbegin(), convertRate.cend(), [&currency](auto c) {return c.first == currency; }) - convertRate.cbegin();

  // output calculated conversion
  std::string str;
  switch (conversion)
  {
    case 0:
      str = std::format("{} {} ==${}\n", amount, convertRate.at(conversion).first, 1 / convertRate.at(conversion).second * amount);
      break;
    case 1:
      str = std::format("{} {} ==${}\n", amount, convertRate.at(conversion).first, 1 / convertRate.at(conversion).second * amount);
      break;
    case 2:
      str = std::format("{} {} ==${}\n", amount, convertRate.at(conversion).first, 1 / convertRate.at(conversion).second * amount);
      break;
    case 3:
      str = std::format("{} {} ==${}\n", amount, convertRate.at(conversion).first, 1 / convertRate.at(conversion).second * amount);
      break;
    case 4:
      str = std::format("{} {} ==${}\n", amount, convertRate.at(conversion).first, 1 / convertRate.at(conversion).second * amount);
      break;
    default:	simple_error("unknown conversion type");
  }

  std::cout << str;

  keep_window_open();
}
