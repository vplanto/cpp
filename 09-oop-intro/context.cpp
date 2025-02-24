#include <iostream>
using namespace std;

class Car {
 public:
  string brand;
  string model;
  int year;

  Car() { cout << "Constructor called" << endl; }
  ~Car() { cout << "Destructor called" << endl; }
};

int main() {
  {
    Car carObj1;
    carObj1.brand = "Toyota";
    carObj1.model = "Corolla";
    carObj1.year = 2020;

    cout << carObj1.brand << " " << carObj1.model << " " << carObj1.year
         << endl;
  }
  cout << "carObj1 already destroyed and not visible" << endl;
  Car carObj1;
  carObj1.brand = "Toyota";
  carObj1.model = "Corolla";
  carObj1.year = 2020;

  cout << carObj1.brand << " " << carObj1.model << " " << carObj1.year << endl;
}
