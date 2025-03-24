/*
 *  Test Class Template (TestClassTemplate.cpp)
 */
#include <iostream>
using namespace std;

template <typename T>
class Number {
 private:
  T value;

 public:
  Number(T value) { this->value = value; };
  T getValue() { return value; }
  void setValue(T value) { this->value = value; };
};

int main() {
  Number<int> i(55);
  cout << i.getValue() << endl;

  Number<double> d(55.66);
  cout << d.getValue() << endl;

  Number<char> c('a');
  cout << c.getValue() << endl;

  Number<string> s("Hello");
  cout << s.getValue() << endl;
}
