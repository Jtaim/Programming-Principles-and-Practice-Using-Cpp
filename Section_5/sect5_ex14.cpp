//written by Jtaim
//date 8 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 14
read (day-of-the-week,value) pairs, collect values for each day in a separate vector.
Ignore illegal days, but accept common synonyms.
escape by "q 5" for day value entry
Print sum and list of values for each day when there is no more input
count of and output rejected entries.
*/

#include "section5.h"

using pType = std::pair <std::vector<std::string>, std::vector<int>>;
using vType = std::vector<pType>;
using numType = pType::second_type::value_type;

numType add(numType n1, numType n2)
{
  if (((n2 > 0) && (n1 > (std::numeric_limits< numType>::max() - n2))) ||
    ((n2 < 0) && (n1 < (std::numeric_limits< numType>::min() - n2))))
  {
    error("overflow error");
  }
  return n1 + n2;
}

int main()
try
{
  constexpr std::string_view termination{"q"};

  vType weekdays{
  { {"sun","sunday"   }, {} },
  { {"mon","monday"   }, {} },
  { {"tue","tuesday"  }, {} },
  { {"wed","wednesday"}, {} },
  { {"thu","thursday" }, {} },
  { {"fri","friday"   }, {} },
  { {"sat","saturday" }, {} }
  };

  unsigned rejects{};
  std::string q{};
  while (q != termination)
  {
    std::cout << "Enter a day of the week (ex:Mon or Monday) and a value. Enter " << termination << " to exit\n";

    std::string day_info;
    (std::getline(std::cin, day_info));
    std::stringstream ss(day_info);
    ss >> day_info;
    std::for_each(day_info.begin(), day_info.end(), [](auto& c) {c = narrow_cast<char>(std::tolower(static_cast<unsigned char>(c))); });

    if (day_info == termination)
    {
      q = day_info;
      continue;
    }

    // check for matching day
    auto validDay = std::find_if(weekdays.begin(), weekdays.end(),
      [&day_info](const auto& wd)
      { return std::find(wd.first.begin(), wd.first.end(), day_info) != wd.first.end(); });

    // check if valid weekday was found?
    if (validDay == weekdays.end())
    {
      ++rejects;
      continue;
    }

    // check if valid weekday value was found?
    numType value{};
    if (ss >> value)
    {
      validDay->second.push_back(value);
    }
    else
    {
      if (value == std::numeric_limits<numType>::max() ||
        value == std::numeric_limits<numType>::min())
      {
        error("Entered number overflowed number type!");
      }
      else if (ss.eof())
      {
        std::cout << "given no value for the day\n";
      }
      else
      {
        error("unknown stream failure or entered invalid value");
      }
      ++rejects;
    }
  }

  //print the results
  std::cout << std::endl;
  for (const auto& d : weekdays)
  {
    numType sum{};
    for (auto num : d.second)
    {
      sum = add(sum, num);
    }
    std::cout << std::left << std::setfill('.') << std::setw(20) << d.first.at(1) << " " << sum << '\n';
  }
  std::cout << "\n\n" << std::left << std::setfill('.') << std::setw(20) << "rejects" << " " << rejects << std::endl;

  keep_window_open();
  return 0;
}
catch (std::exception& e)
{
  std::cerr << "error: " << e.what() << '\n';
  keep_window_open();
  return 1;
}
catch (...)
{
  std::cerr << "Oops: unknown exception!\n";
  keep_window_open();
  return 2;
}
