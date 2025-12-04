#include <iostream>
#include <map>      // std::map - асоціативний контейнер (червоно-чорне дерево)
#include <string>

int main() {
  // Створення map з рядків у цілі числа
  // std::map - відсортований асоціативний контейнер (ключі відсортовані)
  // Складність операцій: O(log n) для вставки, пошуку, видалення
  std::map<std::string, int> myMap;

  // Вставка даних у map
  // Оператор [] створює новий елемент, якщо ключ не існує
  myMap["apple"] = 1;
  myMap["banana"] = 2;
  myMap["cherry"] = 3;

  // Отримання та виведення даних
  // Оператор [] повертає значення за ключем (створює новий елемент, якщо не існує)
  std::cout << "apple: " << myMap["apple"] << std::endl;
  std::cout << "banana: " << myMap["banana"] << std::endl;
  std::cout << "cherry: " << myMap["cherry"] << std::endl;

  return 0;
}