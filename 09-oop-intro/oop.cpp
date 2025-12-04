#include <iostream>

// Демонстрація віртуальних функцій та поліморфізму
class Parent {
 protected:
  int i;  // protected - доступний в класі та похідних класах

 public:
  Parent() : i(0) {}  // Конструктор зі списком ініціалізації

  int getI() const { return i; }  // const метод - не змінює стан об'єкта

  void increment1() { increment2(); }  // Викликає віртуальну функцію

  // virtual - віртуальна функція, може бути перевизначена в похідних класах
  virtual void increment2() { i++; }
};

class Child : public Parent {
 public:
  // override - явне вказівка на перевизначення віртуальної функції
  // УВАГА: рекурсивний виклик increment1() -> increment2() -> increment1()...
  void increment2() override { increment1(); }
};

int main() {
  Child child;
  child.increment1();  // Викликає increment2() з Child, що викликає increment1()...
  child.increment2();  // Прямий виклик increment2() з Child
  std::cout << "Value of i: " << child.getI() << std::endl;
  return 0;
}
