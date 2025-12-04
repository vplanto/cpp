#include <iostream>
using namespace std;

// Базовий клас (батьківський клас)
class Vehicle {
 public:
  string brand = "Ford";  // Ініціалізація членів при оголошенні (C++11)
  void honk() { cout << "Tuut, tuut! \n"; }
};

// Похідний клас (дочірній клас): public наслідування
// Car наслідує всі public та protected члени Vehicle
class Car : public Vehicle {
 public:
  string model = "Mustang";
};

int main() {
  Car myCar;
  myCar.honk();  // Виклик успадкованого методу
  cout << myCar.brand + " " + myCar.model << endl;  // Доступ до успадкованого та власного членів
  return 0;
}
