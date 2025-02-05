#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include "base-types.hpp"
#include "shape.hpp"
#include "makeShape.hpp"

using namespace brevnov;

int main()
{
  std::cout << std::fixed << std::setprecision(1);
  size_t start_count_shape = 30;
  CompositeShape Cs(start_count_shape);
  std::string input_shape;
  point_t scale_p;
  double ratio = 0.0;
  bool isIncorrectParameters = false;
  bool scaleCommand = false;
  Shape * new_shape = nullptr;
  std::cin >> input_shape;
  while (input_shape & scaleCommand == false)
  {
    if (std::cin.eof())
    {
      std::cerr << "EOF!!\n";
      return 1;
    }
    else if (input_shape == "SCALE")
    {
      try
      {
        scale_p = scale(std::cin);
      }
      catch (const std::invalid_argument& f)
      {
        std::cerr << "incorrect scale point\n";
        return 1;
      }
      std::cin >> ratio;
      if (ratio <= 0.0)
      {
        std::cerr << "Incorrect retio\n";
        return 1;
      }
      scaleCommand = true;
      break;
    }
    else
    {
      try
      {
        new_shape = make_shape(input_shape, std::cin);
        if (new_shape)
        {
          Cs.push_back(new_shape);
        }
      }
      catch (const std::bad_alloc & e)
      {
        std::cerr << "Not enough memory!\n";
        return 1;
      }
      if (!new_shape)
      {
        isIncorrectParameters = true;
      }
    }
    std::cin >> input_shape;
  }
  if (isIncorrectParameters)
  {
    std::cerr << "Some parameters were incorrect\n";
  }
  if (Cs.empty())
  {
    std::cerr << "Not a single figure was read\n";
    return 1;
  }
  if (!scaleCommand)
  {
    std::cerr << "No SCALE command!\n";
    return 1;
  }
  std::cout << std::setprecision(1);
  std::cout << Cs.getArea() << " ";
  print_frame_coordinates(Cs, std::cout);
  std::cout << "\n";
  Cs.scale(ratio, scale_p);
  std::cout << Cs.getArea() << " ";
  print_frame_coordinates(Cs, std::cout);
  std::cout << "\n";
  return 0;
}
