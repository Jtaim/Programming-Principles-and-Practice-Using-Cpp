//written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition


/**
 * Section 3 Drill. This drill is to write a program that produces a
 * simple form letter based on user input.
 */

#include "section3.h"

int main()
{
  using namespace std;

  constexpr unsigned minAge{0};
  constexpr unsigned maxAge{110};

  cout << "Enter the name of the person you want to write to:\n";
  string first_name;
  cin >> first_name;
  cout << std::format("Dear {},\n", first_name);

  cout << "\tHow are you? I am fine. I'm writing a simple program in C++\n";

  cout << "Enter a friends name:\n";
  cin >> first_name;
  cout << std::format("Have you seen {} lately?\n", first_name);

  cout << "What is your friends gender? (Enter m for male and f for female)\n";
  char gender{};
  //check for correct entry
  while (cin >> gender)
  {
    gender = tolower(static_cast<unsigned char>(gender));
    if (gender == 'm' || gender == 'f')
    {
      cout << std::format("If you see {} ask {} to call me.\n", first_name, ((gender == 'm') ? "him" : "her"));
      break;
    }
    cout << std::format("unrecognized gender selection ({}), please reenter: ", gender);
  }

  cout << "How old are you?\n";
  int age{};
  //check for valid age and valid cin to int
  if (cin >> age && age > minAge && age < maxAge)
  {
    cout << std::format("I hear you just had a birthday and you are {} years old.\n", age);
    if (age < 12)
    {
      cout << std::format("Next year you will be {}.\n", age + 1);
    }
    else if (age == 17)
    {
      cout << "Next year you will be able to vote.\n";
    }
    else if (age > 70)
    {
      cout << "I hope you are enjoying retirement.\n";
    }
    cout << "Yours sincerely,\n\nJ\n";
  }
  else
  {
    simple_error("you're kidding!");
  }

  keep_window_open();
  return 0;
}
