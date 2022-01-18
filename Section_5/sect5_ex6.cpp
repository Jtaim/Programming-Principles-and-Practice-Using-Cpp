//written by Jtaim
//date 6 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
sect 5 exercise 6
Celsius to Fahrenheit converter
Fahrenheit to Celsius converter
*/

#include "section5.h"

// converts Celsius to Fahrenheit
double ctof(double c)
{
  if (c < -273.15)
  {
    //throw error if value given in Celsius is below -273.15
    error("Can not be below absolute zero!\n");
  }
  double celsiusToFahrenheit{9.0 / 5.0 * c + 32.0};
  return celsiusToFahrenheit;
}

// converts Fahrenheit to Celsius
double ftoc(double f)
{
  double fahrenheitToCelsius{5.0 / 9.0 * (f - 32.0)};

  if (fahrenheitToCelsius < -273.15)
  {
    //throw error if value given in Celsius is below -273.15
    error("Can not be below absolute zero!\n");
  }
  return fahrenheitToCelsius;
}

int main()
try
{
  using pType = std::pair<char, double>;
  pType inputTempearure{};

  std::cout << "Enter a temperature and unit of temperature (c = Celsius, f = Fahrenheit)\n";

  // get measurement
  if (!(std::cin >> inputTempearure.second))
  {
    error("entered non-numeric temperature.");
  }

  // get unit
  std::cin >> inputTempearure.first;
  inputTempearure.first = narrow_cast<char, int>(tolower(static_cast<unsigned char>(static_cast<unsigned char>(inputTempearure.first))));

  // convert temperatures
  pType temperatureConverted{};
  switch (inputTempearure.first)
  {
  case 'c':
    temperatureConverted.second = ctof(inputTempearure.second);
    temperatureConverted.first = 'f';
    break;
  case 'f':
    temperatureConverted.second = ftoc(inputTempearure.second);
    temperatureConverted.first = 'c';
    break;
  default:
    error("Unknown unit of measure for temperature.");
  }

  std::cout << "Converted temperature is " << temperatureConverted.second << temperatureConverted.first << std::endl;

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
