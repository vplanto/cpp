#include <iostream>

// Демонстрація проблем інкапсуляції та повернення посилань на приватні члени
class MyClass {
 public:
  MyClass(int val = 0) { this->value = val; }  // this-> - явне вказівка на поточний об'єкт

  // const метод повертає const посилання на приватний член
  // ПРОБЛЕМА: повертається посилання на приватний член, що порушує інкапсуляцію
  const int &getValueByReference() const { return value; }

  // const метод повертає значення (безпечніше)
  const int getValue() const { return value; }

 private:
  int value;
};

int main() {
  MyClass obj(10);

  // Отримання const посилання на приватний член
  const int &val = obj.getValueByReference();

  // Спроба змінити приватний член
  // Це викличе помилку компіляції, бо val - const посилання
  // val = 20;

  // Однак, якщо прибрати const через const_cast, можна змінити приватний член
  // УВАГА: це порушує інкапсуляцію та може призвести до невизначеної поведінки!
  const_cast<int &>(val) = 20;

  // Приватний член було змінено через посилання
  std::cout << "Modified value: " << obj.getValueByReference() << std::endl;

  // Демонстрація адрес: посилання вказує на той самий об'єкт
  std::cout << "Size of obj with reference " << &obj.getValueByReference()
            << " is " << sizeof(obj.getValueByReference()) << " bytes"
            << std::endl;

  int t = obj.getValue();  // Копія значення (інша адреса)
  std::cout << "Size of obj with reference " << &t << " is " << sizeof(t)
            << " bytes" << std::endl;

  // Інша проблема: можливий виклик конструктора копіювання
  MyClass obj2(obj);  // Конструктор копіювання (створює копію)
  std::cout << "Size of obj2 with reference " << &obj2.getValueByReference()
            << " is " << sizeof(obj2.getValueByReference()) << " bytes"
            << std::endl;

  // Або оператор присвоєння копіювання
  MyClass obj3;
  obj3 = obj;  // Оператор присвоєння копіювання
  std::cout << "Size of obj3 with reference " << &obj3.getValueByReference()
            << " is " << sizeof(obj3.getValueByReference()) << " bytes"
            << std::endl;

  return 0;
}
