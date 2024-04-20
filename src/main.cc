#include <cmath>
#include <iostream>

#include "header/fixed_point.h"

int main() {
  FixedPoint a(1.23f);
  FixedPoint<12, int16_t> b(4.567f);

  FixedPoint c = a + b;
  std::cout << c.GetFloat() << std::endl;

  c = a - b;
  std::cout << c.GetFloat() << std::endl;

  c = a * b;
  std::cout << c.GetFloat() << std::endl;

  c = a / b;
  std::cout << c.GetFloat() << std::endl;


  return 0;
}