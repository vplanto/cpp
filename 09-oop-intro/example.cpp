#include <iostream>

// Демонстрація спеціальних функцій-членів класу
class Example {
 public:
  // Конструктор за замовчуванням
  Example() { std::cout << "Default constructor called" << std::endl; }

  // Деструктор
  ~Example() { std::cout << "Destructor called" << std::endl; }

  // Конструктор копіювання (приймає const посилання на інший об'єкт)
  Example(const Example& other) {
    std::cout << "Copy constructor called" << std::endl;
  }

  // Оператор присвоєння копіювання
  // Повертає посилання на поточний об'єкт (*this) для ланцюжкового присвоєння
  Example& operator=(const Example& other) {
    std::cout << "Copy assignment operator called" << std::endl;
    return *this;  // *this - розіменування вказівника на поточний об'єкт
  }
};

int main() {
  Example obj1;              // Викликається конструктор за замовчуванням
  Example obj2 = obj1;       // Викликається конструктор копіювання (ініціалізація)
  Example obj3;              // Викликається конструктор за замовчуванням
  obj3 = obj1;                // Викликається оператор присвоєння копіювання
  Example obj4(obj1);        // Викликається конструктор копіювання (явний виклик)
  return 0;
  // Деструктори викликаються в зворотному порядку створення
}
