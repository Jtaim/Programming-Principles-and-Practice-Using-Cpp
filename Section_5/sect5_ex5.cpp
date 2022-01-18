//written by Jtaim
//date 5 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
sect 5 exercise 5
Celsius to Kelvin converter
Added Kelvin to Celsius converter
*/
#include "section5.h"

// converts Celsius to Kelvin
double ctok(double c)
{
  if (c < -273.15)
  {
    //throw error if value given in Celsius is below -273.15
    error("Can not be below absolute zero!\n");
  }
  constexpr double conversion_constant{273.15};
  double celsiusToKelvin{c + conversion_constant};
  return celsiusToKelvin;
}

// converts Kelvin to Celsius
double ktoc(double k)
{
  if (k < 0)
  {
    //there are no negative kelvin values
    error("Can not be below absolute zero!\n");
  }
  constexpr double conversion_constant{273.15};
  double kelvinToCelsius{k - conversion_constant};
  return kelvinToCelsius;
}

int main()
{
  using pType = std::pair<char, double>;
  pType inputTempearure{};

  try
  {
    std::cout << "Enter a temperature and unit of temperature (c = Celsius, k = Kelvin)\n";

    // get measurement
    if (!(std::cin >> inputTempearure.second))
    {
      error("entered non-numeric temperature.");
    }

    // get unit
    std::cin >> inputTempearure.first;
    inputTempearure.first = narrow_cast<char, int>(tolower(static_cast<unsigned char>(inputTempearure.first)));

    // convert temperatures
    pType temperatureConverted{};
    switch (inputTempearure.first)
    {
    case 'c':
      temperatureConverted.second = ctok(inputTempearure.second);
      temperatureConverted.first = 'k';
      break;
    case 'k':
      temperatureConverted.second = ktoc(inputTempearure.second);
      temperatureConverted.first = 'c';
      break;
    default:
      error("Unknown unit of measure for temperature.");
    }

    std::cout << "Converted temperature is " << temperatureConverted.second << temperatureConverted.first << std::endl;

    keep_window_open();
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
  return 0;
}
