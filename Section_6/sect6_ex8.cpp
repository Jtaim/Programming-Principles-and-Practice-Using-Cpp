//Written by Jtaim
//Date 1 Dec 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 6 exercise 8
Rewrite Section 5 exercise 12 Bulls and Cows game to use 4 letters not 4 numbers.
*/

#include "section6.h"

using vType = std::vector<char>;
bool get_guesses(vType& input, std::size_t length);
int get_bulls(vType& guesses, vType& setSequence);
int get_cows(vType& guesses, vType& setSequence);
const vType::value_type foundMark = '?';

int main()
{
  using std::cout;

  vType const setLetters{'a', 'b', 'c', 'd'};
  //vType const setLetters{'a', 'a', 'a', 'a'};

  vType guesses{};

  cout << "Guess " << setLetters.size() << " letters in the range of a - z to guess what I have.\n";
  cout << "If guess a correct letter and the correct location will get a Bull.\n";
  cout << "If guess a correct letter but not the correct location then will get a Cow.\n";
  cout << "Example: My set is abcd and your guess was acbe, so there are 2 Cows (b and c)  1 Bull (a).\n\n";
  cout << "Enter your guess.\n";

  try
  {
    while (get_guesses(guesses, setLetters.size()))
    {
      if (guesses == setLetters)
      {
        std::cout << "You have " << setLetters.size() << " Bulls, Congratulations!\n";
        break;
      }
      else
      {
        vType letters = setLetters;
        auto bulls = get_bulls(guesses, letters);
        auto cows = get_cows(guesses, letters);

        std::cout << "The result is " << cows << (cows == 1 ? " Cow" : " Cows");
        std::cout << " and " << bulls << (bulls == 1 ? " Bull" : " Bulls") << ". Try again.\n";
        guesses.clear();	// clear for new set of guesses
      }
    }
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

  cout << "Bye\n";
  keep_window_open();
  return 0;
}

/* function to get user input for letters a - z.
INPUT:  vType reference to store guesses.
        size_t for length of number to guess.
OUPUT:  bool true = got valid guesses
        bool false = insufficient guess entered
ERROR:  invalid guess
*/
bool get_guesses(vType& input, std::size_t length)
{
  std::string user_guess;
  std::getline(std::cin, user_guess);

  if (user_guess.size() != length)
  {
    std::cout << "number of guesses entered must be " << length << " characters\n";
    return false;
  }

  for (unsigned char guess : user_guess)
  {
    if (isalpha(guess))
    {
      vType::value_type character = guess;
      input.push_back(character);
    }
    else
    {
      error("Bad entry data!");
    }
  }
  return true;
}

/* function to bulls.
INPUT:  vType reference to user input guesses.
        vType reference to character to guess.
OUPUT:  int for number of bulls found
ERROR:  input vector sizes do not match.
modifies set sequence by setting matching elements to a none alpha character
*/
int get_bulls(vType& guesses, vType& setSequence)
{
  if (guesses.size() != setSequence.size())
  {
    error("guess and answer size do not match!");
  }

  int bulls{};
  for (auto i{guesses.begin()}, j{setSequence.begin()}; i < guesses.cend(); ++i, ++j)
  {
    if (*i == *j)
    {
      ++bulls;
      *i = *j = foundMark;
    }
  }
  return bulls;
}

/* function to cows.
INPUT:  vType reference to user input guesses.
        vType reference to character to guess.
OUPUT:  int for number of cows found
ERROR:  input vector sizes do not match.
modifies set sequence by setting matching elements to a none alpha character
*/
int get_cows(vType& guesses, vType& setSequence)
{
  if (guesses.size() != setSequence.size())
  {
    error("input vector sizes do not match!");
  }

  int cows{};
  for (auto& guess : guesses)
  {
    if (guess != foundMark)
    {
      auto itr = std::find(setSequence.begin(), setSequence.end(), guess);
      if (itr != setSequence.cend())
      {
        ++cows;
        guess = *itr = foundMark;
      }
    }
  }
  return cows;
}
