//written by Jtaim
//date 2 Apr 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 20.
Modify exercise 19 so that when you enter a name, the program will output the
corresponding score or name not found.
*/

#include "section4.h"

int main()
{
  using pType = std::pair<std::string, double>;
  pType name_score;
  pType termination{"NoName",0};
  std::vector<pType> ranks{{"Moe",1}, {"Larry",2}, {"Curly", 3},{"Shemp",4}};

  std::cout << "Enter a name to find a score.\n";
  for (auto i{ranks.begin()}; i != ranks.end(); ++i)
  {
    std::cout << i->first << (((i + 1) != ranks.end()) ? ", " : "\n");
  }

  for (std::string name; std::cin >> name && name != termination.first; )
  {
    // set name so first letter is capitalized and rest lower case
    name[0] = (std::toupper(static_cast<unsigned char>(name[0])));
    std::transform(name.begin() + 1, name.end(), name.begin() + 1,
      [](unsigned char c) {return static_cast<char>(std::tolower(c)); });

    // is name in list
    auto itr{std::find_if(ranks.cbegin(), ranks.cend(), [&name](const auto& ns) {return ns.first == name; })};
    if (ranks.cend() == itr)
    {
      std::cout << "Name not found.\n";
    }
    else
    {
      std::cout << name << "'s score is " << itr->second << ".\n";
    }
  }

  keep_window_open();
  return 0;
}
