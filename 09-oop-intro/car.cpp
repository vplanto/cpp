#include <iostream>
using namespace std;

// Простий клас з public членами (відсутня інкапсуляція)
class Car {
 public:
  string brand;  // public члени - доступні ззовні класу
  string model;
  int year;
};

int main() {
  Car carObj1;  // Створення об'єкта класу Car
  carObj1.brand = "Toyota";  // Прямий доступ до public членів
  carObj1.model = "Corolla";
  carObj1.year = 2020;

  cout << carObj1.brand << " " << carObj1.model << " " << carObj1.year << endl;
  return 0;
}
