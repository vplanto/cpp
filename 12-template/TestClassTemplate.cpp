/*
 *  Тестування шаблону класу (TestClassTemplate.cpp)
 */
#include <iostream>
using namespace std;

// Шаблон класу: template <typename T> - T є параметром типу
template <typename T>
class Number {
 private:
  T value;  // Член типу T (визначається під час інстанціації)

 public:
  Number(T value) { this->value = value; };
  T getValue() { return value; }
  void setValue(T value) { this->value = value; };
};

int main() {
  // Number<int> - інстанціація шаблону класу для типу int
  Number<int> i(55);
  cout << i.getValue() << endl;

  Number<double> d(55.66);  // Інстанціація для double
  cout << d.getValue() << endl;

  Number<char> c('a');  // Інстанціація для char
  cout << c.getValue() << endl;

  Number<string> s("Hello");  // Інстанціація для string
  cout << s.getValue() << endl;
}
