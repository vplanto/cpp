#include <iostream>

class Example {
 public:
  // Default constructor
  Example() { std::cout << "Default constructor called" << std::endl; }

  // Default destructor
  ~Example() { std::cout << "Destructor called" << std::endl; }

  // Default copy constructor
  Example(const Example& other) {
    std::cout << "Copy constructor called" << std::endl;
  }

  // Default copy assignment operator
  Example& operator=(const Example& other) {
    std::cout << "Copy assignment operator called" << std::endl;
    return *this;
  }
};

int main() {
  Example obj1;
  Example obj2 = obj1;
  Example obj3;
  obj3 = obj1;
  Example obj4(obj1);
  return 0;
}
