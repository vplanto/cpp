#include <iostream>

int y = 25;

std::string foo() {
  std::string x = "I`m " + std::to_string(y);
  return x;
}

int bar() {
  int x = 42;
  y = x - y;
  return x + y;
}

int main() {
  std::cout << foo() << std::endl;
  std::cout << bar() << std::endl;

  return 0;
}
