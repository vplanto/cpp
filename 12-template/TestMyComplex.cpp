/* Тестова програма для шаблону класу MyComplex (TestMyComplex.cpp) */
#include <iomanip>
#include <iostream>

#include "MyComplex.h"

int main() {
  std::cout << std::fixed << std::setprecision(2);

  // Інстанціація шаблону для типу double
  MyComplex<double> c1(3.1, 4.2);
  std::cout << c1 << std::endl;  // (3.10,4.20) - використовується перевантажений <<
  MyComplex<double> c2(3.1);  // Другий параметр за замовчуванням = 0
  std::cout << c2 << std::endl;  // (3.10,0.00)

  // Використання перевантаженого оператора +
  MyComplex<double> c3 = c1 + c2;
  std::cout << c3 << std::endl;  // (6.20,4.20)
  c3 = c1 + 2.1;  // c + double
  std::cout << c3 << std::endl;  // (5.20,4.20)
  c3 = 2.2 + c1;  // double + c
  std::cout << c3 << std::endl;  // (5.30,4.20)

  // Використання перевантаженого оператора +=
  c3 += c1;
  std::cout << c3 << std::endl;  // (8.40,8.40)
  c3 += 2.3;  // c += double
  std::cout << c3 << std::endl;  // (10.70,8.40)

  // Префіксний та постфіксний інкремент
  std::cout << ++c3 << std::endl;  // (11.70,8.40) - спочатку інкремент, потім виведення
  std::cout << c3++ << std::endl;  // (11.70,8.40) - спочатку виведення, потім інкремент
  std::cout << c3 << std::endl;    // (12.70,8.40) - після інкременту

  // c1+c2 = c3;  // Помилка: c1+c2 повертає const (не можна змінювати)
  // c1++++;      // Помилка: c1++ повертає const (не можна подвійний інкремент)

  // MyComplex<int> c4 = 5;  // Помилка: неявне перетворення заборонене (explicit)
  MyComplex<int> c4 = (MyComplex<int>)5;  // Явне приведення типу дозволене
  std::cout << c4 << std::endl;           // (5,0)

  MyComplex<int> c5;
  std::cout << "Enter a complex number in (real,imag): ";
  std::cin >> c5;  // Використовується перевантажений >>
  if (std::cin.good()) {
    std::cout << c5 << std::endl;
  } else {
    std::cerr << "Invalid input" << std::endl;
  }
  return 0;
}
