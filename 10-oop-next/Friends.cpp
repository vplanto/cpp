class MyClass {
 private:
  int myPrivateVar;

 public:
  MyClass() : myPrivateVar(0) {}

  // Friend function declaration
  friend void modifyPrivateVar(MyClass &);
};

// Friend function definition
void modifyPrivateVar(MyClass &obj) {
  // Accessing private member from the friend function
  obj.myPrivateVar = 5;
}

int main() {
  MyClass obj;
  modifyPrivateVar(
      obj);  // This is fine, modifyPrivateVar is a friend of MyClass
  return 0;
}
