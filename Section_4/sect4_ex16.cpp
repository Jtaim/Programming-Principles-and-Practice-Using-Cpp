//written by Jtaim
//date 2 Apr 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 16.
A program that finds the mode of a set of positive integers
The "mode" is the value that occurs most often.
If no number is repeated, then there is no mode for the list.
Refer to drill 3
*/

#include "section4.h"

int main()
{
  constexpr char termination{'|'};

  using vType = std::vector<int>;
  std::cout << "Enter a sequence of numbers to find the MODE. (use '|' to indicate last number)\n";

  vType sequence;  // vector to hold input sequence
  char c{};
  while (c != termination)
  {
    vType::value_type enteredValue{};
    std::cin >> enteredValue;
    if (!std::cin.good())
    {
      std::cin.clear();
      std::cin.get(c);
      if (c != termination)
      {
        std::cout << "Invalid number or termination, please try again.\n";
      }
    }
    else
    {
      sequence.push_back(enteredValue);
    }
  }

  if (sequence.empty())
  {
    std::cout << "nothing entered\n";
  }
  else
  {
    std::sort(sequence.begin(), sequence.end());
    vType::value_type mode{};
    vType::difference_type count{};

    // search sorted vector for most duplicates
    for (auto i{sequence.cbegin()}, next{sequence.cbegin()}; i != sequence.end(); i = next)
    {
      next = std::find_if_not(i, sequence.cend(), [i](auto comp) {return *i == comp; });
      auto temp_count{next - i};
      if (temp_count >= count)
      {
        count = temp_count;
        mode = *i;
      }
    }

    // print out the MODE
    if (count > 1)
    {
      std::cout << "The MODE of entered sequence is " << mode << ".\n";
      std::cout << mode << " was found " << count << " times.\n";
    }
    else
    {
      std::cout << "There is no MODE from this set.\n";
    }
  }


  keep_window_open();
  return 0;
}
