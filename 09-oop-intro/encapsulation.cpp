#include <iostream>

class MyClass {
 public:
  MyClass(int val = 0) { this->value = val; }

  // Const method returning a reference to a private member
  const int &getValueByReference() const { return value; }

  // Const method returning by value to a private member
  const int getValue() const { return value; }

 private:
  int value;
};

int main() {
  MyClass obj(10);

  // Get a reference to the private member
  const int &val = obj.getValueByReference();

  // Attempt to modify the private member
  // This will cause a compile error because val is a const reference
  // val = 20;

  // However, if we cast away the const-ness, we can modify the private member
  const_cast<int &>(val) = 20;

  // Now the private member has been modified
  std::cout << "Modified value: " << obj.getValueByReference() << std::endl;

  std::cout << "Size of obj with reference " << &obj.getValueByReference()
            << " is " << sizeof(obj.getValueByReference()) << " bytes"
            << std::endl;

  int t = obj.getValue();
  std::cout << "Size of obj with reference " << &t << " is " << sizeof(t)
            << " bytes" << std::endl;

  // another problem is possible calling copy constructor
  MyClass obj2(obj);
  std::cout << "Size of obj2 with reference " << &obj2.getValueByReference()
            << " is " << sizeof(obj2.getValueByReference()) << " bytes"
            << std::endl;

  // or a copy assignment operator
  MyClass obj3;
  obj3 = obj;
  std::cout << "Size of obj3 with reference " << &obj3.getValueByReference()
            << " is " << sizeof(obj3.getValueByReference()) << " bytes"
            << std::endl;

  return 0;
}
