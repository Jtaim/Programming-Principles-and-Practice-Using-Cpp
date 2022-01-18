//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 10.
 Write a program that plays the game “Rock, Paper, Scissors.”
 If you are not familiar with the game do some research (e.g., on the web using Google).
 Research is a common task for programmers. Use a switch-statement to solve this exercise.
 Also, the machine should give random answers (i.e., select the next rock, paper, or scissors randomly).
 Real randomness is too hard to provide just now, so just build a vector with a sequence of values to be
 used as “the next value.” If you build the vector into the program, it will always play the same game,
 so maybe you should let the user enter some values.
 Try variations to make it less easy for the user to guess which move the machine will make next.
*/

#include "section4.h"

int main()
{
  //Will be used to obtain a seed for the random number engine
  std::random_device rd;
  //Standard mersenne_twister_engine seeded with rd()
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 2);

  constexpr auto rps = std::to_array<std::string_view>({"rock", "paper", "scissors"});

  bool playAgain{false};
  do
  {
    std::cout << "Select (1)Rock (2)Paper (3)Scissors ";
    // check for proper input
    unsigned playersSelection{};
    std::cin >> playersSelection;

    // if is an integer select -1 to adjust so can just index the array.
    // else cin failed will check if player entered a string.
    if (std::cin.good())
    {
      playersSelection -= 1;
    }
    else
    {
      std::cin.clear();
      std::string selection;
      std::cin >> selection;
      std::transform(selection.begin(), selection.end(), selection.begin(),
        [](unsigned char c) { return static_cast<unsigned char>(std::tolower(c)); });
      playersSelection = static_cast<unsigned>(std::find(rps.cbegin(), rps.cend(), selection) - rps.begin());
    }

    if (playersSelection >= rps.size())
    {
      simple_error("player selection was not valid");
    }
    else
    {
      auto computersSelection{dis(gen)};  //have only 3 selections gets random selection between 0 and 2

      std::cout << "Your selection was " << rps.at(playersSelection) << " the computer selected was "
        << rps.at(computersSelection) << std::endl;

      std::cout << "The winner is ";
      switch (playersSelection)
      {
      case 0:
        std::cout << (computersSelection == 0 ? "a tie" : computersSelection == 2 ? "player" : "computer");
        break;
      case 1:
        std::cout << (computersSelection == 1 ? "a tie" : computersSelection == 0 ? "player" : "computer");
        break;
      case 2:
        std::cout << (computersSelection == 2 ? "a tie" : computersSelection == 1 ? "player" : "computer");
        break;
      default:
        // should never reach this state with previous if statement
        break;
      }
      std::cout << std::endl;
    }

    std::cout << "\nWould you like to play again (y or n)" << std::endl;
    char c;
    std::cin >> c;
    // check for proper input
    c == 'y' ? playAgain = true : playAgain = false;
  } while (playAgain);

  keep_window_open();
  return 0;
}
