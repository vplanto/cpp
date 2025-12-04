#include <iostream>
using namespace std;

// Базовий клас
class Base {
 private:
  int privateVar = 1;  // Доступний тільки всередині Base
 protected:
  int protectedVar = 2;  // Доступний в Base та похідних класах
 public:
  int publicVar = 3;  // Доступний будь-де
};

// Похідний клас з public наслідуванням
// public члени Base залишаються public, protected - protected
class PublicDerived : public Base {
 public:
  void display() {
    // privateVar НЕ доступний
    // cout << privateVar; // Помилка компіляції

    cout << "Public Derived - Protected Var: " << protectedVar
         << endl;                                                  // Доступний
    cout << "Public Derived - Public Var: " << publicVar << endl;  // Доступний
  }
};

// Похідний клас з protected наслідуванням
// public та protected члени Base стають protected в ProtectedDerived
class ProtectedDerived : protected Base {
 public:
  void display() {
    // privateVar НЕ доступний
    // cout << privateVar; // Помилка компіляції

    cout << "Protected Derived - Protected Var: " << protectedVar
         << endl;  // Доступний
    cout << "Protected Derived - Public Var: " << publicVar
         << endl;  // Доступний (але стає protected)
  }
};

// Похідний клас з private наслідуванням
// public та protected члени Base стають private в PrivateDerived
class PrivateDerived : private Base {
 public:
  void display() {
    // privateVar НЕ доступний
    // cout << privateVar; // Помилка компіляції

    cout << "Private Derived - Protected Var: " << protectedVar
         << endl;  // Доступний
    cout << "Private Derived - Public Var: " << publicVar
         << endl;  // Доступний (але стає private)
  }
};

int main() {
  PublicDerived publicObj;
  publicObj.display();
  // public члени Base залишаються public
  cout << "Accessing Public Var from PublicDerived object: "
       << publicObj.publicVar << endl;

  ProtectedDerived protectedObj;
  protectedObj.display();
  // protectedObj.publicVar; // Помилка: publicVar стає protected в ProtectedDerived

  PrivateDerived privateObj;
  privateObj.display();
  // privateObj.publicVar; // Помилка: publicVar стає private в PrivateDerived

  return 0;
}
