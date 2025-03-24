/* Test Driver for MyComplex template class (TestMyComplex.cpp) */
#include <iomanip>
#include <iostream>

#include "MyComplex.h"

int main() {
  std::cout << std::fixed << std::setprecision(2);

  MyComplex<double> c1(3.1, 4.2);
  std::cout << c1 << std::endl;  // (3.10,4.20)
  MyComplex<double> c2(3.1);
  std::cout << c2 << std::endl;  // (3.10,0.00)

  MyComplex<double> c3 = c1 + c2;
  std::cout << c3 << std::endl;  // (6.20,4.20)
  c3 = c1 + 2.1;
  std::cout << c3 << std::endl;  // (5.20,4.20)
  c3 = 2.2 + c1;
  std::cout << c3 << std::endl;  // (5.30,4.20)

  c3 += c1;
  std::cout << c3 << std::endl;  // (8.40,8.40)
  c3 += 2.3;
  std::cout << c3 << std::endl;  // (10.70,8.40)

  std::cout << ++c3 << std::endl;  // (11.70,8.40)
  std::cout << c3++ << std::endl;  // (11.70,8.40)
  std::cout << c3 << std::endl;    // (12.70,8.40)

  // c1+c2 = c3;  // error: c1+c2 returns a const
  // c1++++;      // error: c1++ returns a const

  // MyComplex<int> c4 = 5;  // error: implicit conversion disabled
  MyComplex<int> c4 = (MyComplex<int>)5;  // explicit type casting allowed
  std::cout << c4 << std::endl;           // (5,0)

  MyComplex<int> c5;
  std::cout << "Enter a complex number in (real,imag): ";
  std::cin >> c5;
  if (std::cin.good()) {
    std::cout << c5 << std::endl;
  } else {
    std::cerr << "Invalid input" << std::endl;
  }
  return 0;
}
