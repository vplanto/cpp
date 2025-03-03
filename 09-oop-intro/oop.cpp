#include <iostream>

class Parent {
 protected:
  int i;

 public:
  Parent() : i(0) {}

  int getI() const { return i; }

  void increment1() { increment2(); }

  virtual void increment2() { i++; }
};

class Child : public Parent {
 public:
  void increment2() override { increment1(); }
};

int main() {
  Child child;
  child.increment1();
  child.increment2();
  std::cout << "Value of i: " << child.getI() << std::endl;
  return 0;
}
