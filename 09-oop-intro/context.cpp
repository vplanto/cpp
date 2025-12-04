#include <iostream>
using namespace std;

class Car {
 public:
  string brand;
  string model;
  int year;

  Car() { cout << "Constructor called" << endl; }   // Конструктор викликається при створенні
  ~Car() { cout << "Destructor called" << endl; }   // Деструктор викликається при знищенні
};

int main() {
  {
    // Блокова область видимості
    Car carObj1;  // Викликається конструктор
    carObj1.brand = "Toyota";
    carObj1.model = "Corolla";
    carObj1.year = 2020;

    cout << carObj1.brand << " " << carObj1.model << " " << carObj1.year
         << endl;
  }  // При виході з блоку викликається деструктор для carObj1
  cout << "carObj1 already destroyed and not visible" << endl;
  Car carObj1;  // Новий об'єкт з тим самим ім'ям (інша область видимості)
  carObj1.brand = "Toyota";
  carObj1.model = "Corolla";
  carObj1.year = 2020;

  cout << carObj1.brand << " " << carObj1.model << " " << carObj1.year << endl;
  // Деструктор викликається автоматично при завершенні main()
}
