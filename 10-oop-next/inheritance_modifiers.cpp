#include <iostream>
using namespace std;

// Base class
class Base {
 private:
  int privateVar = 1;  // Accessible only within Base
 protected:
  int protectedVar = 2;  // Accessible in Base and derived classes
 public:
  int publicVar = 3;  // Accessible anywhere
};

// Derived class using public inheritance
class PublicDerived : public Base {
 public:
  void display() {
    // privateVar is NOT accessible
    // cout << privateVar; // This would throw an error

    cout << "Public Derived - Protected Var: " << protectedVar
         << endl;                                                  // Accessible
    cout << "Public Derived - Public Var: " << publicVar << endl;  // Accessible
  }
};

// Derived class using protected inheritance
class ProtectedDerived : protected Base {
 public:
  void display() {
    // privateVar is NOT accessible
    // cout << privateVar; // This would throw an error

    cout << "Protected Derived - Protected Var: " << protectedVar
         << endl;  // Accessible
    cout << "Protected Derived - Public Var: " << publicVar
         << endl;  // Accessible
  }
};

// Derived class using private inheritance
class PrivateDerived : private Base {
 public:
  void display() {
    // privateVar is NOT accessible
    // cout << privateVar; // This would throw an error

    cout << "Private Derived - Protected Var: " << protectedVar
         << endl;  // Accessible
    cout << "Private Derived - Public Var: " << publicVar
         << endl;  // Accessible
  }
};

int main() {
  PublicDerived publicObj;
  publicObj.display();
  cout << "Accessing Public Var from PublicDerived object: "
       << publicObj.publicVar << endl;

  ProtectedDerived protectedObj;
  protectedObj.display();
  // protectedObj.publicVar; // This would throw an error as publicVar is
  // protected in ProtectedDerived

  PrivateDerived privateObj;
  privateObj.display();
  // privateObj.publicVar; // This would throw an error as publicVar is private
  // in PrivateDerived

  return 0;
}
