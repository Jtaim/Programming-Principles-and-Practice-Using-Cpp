//written by Jtaim
//date 2 Apr 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 19.
A program where you first enter a set of name-and-value pairs, such as Joe 17 and Barbara 22.
For each pair, add the name to a vector called names and the number to a vector called scores
(in corresponding positions, so that if names[7]=="Joe" then scores[7]==17).
Terminate input with NoName 0.
Check that each name is unique and terminated with an error message if a name is entered twice.
Write out all the (name, score) pairs, one per line.
*/

#include "section4.h"

int main()
{
  using pType = std::pair<std::string, double>;
  pType name_score;
  pType termination{"NoName",0};
  std::vector<pType> ranks;

  std::cout << "Enter names and scores:\n";
  while (std::cin >> name_score.first >> name_score.second)
  {
    if (name_score.first == termination.first && name_score.second == termination.second)
    {
      break;
    }
    std::transform(name_score.first.begin(), name_score.first.end(), name_score.first.begin(),
      [](unsigned char name) { return static_cast<char>(::tolower(name)); });

    // check if duplicated
    if (ranks.cend() != std::find_if(ranks.cbegin(), ranks.cend(),
      [&name_score](const auto& ns) {return ns.first == name_score.first; }))
    {
      simple_error("found a duplicated name");
    }

    ranks.push_back(name_score);
  }

  if (ranks.empty())
  {
    std::cout << "nothing entered\n";
  }
  else
  {
    // print contents to screen
    for (const auto& i : ranks)
    {
      std::cout << "name: " << i.first << "\tscore: " << i.second << std::endl;
    }
  }

  keep_window_open();
  return 0;
}
