#include <iostream>
#include <map>      // std::map - асоціативний контейнер
#include <string>
#include <vector>   // std::vector для зберігання списку оцінок

int main() {
  // Створення map з рядків у вектори цілих чисел
  // Кожен студент має список оцінок (vector<int>)
  // std::map автоматично сортує ключі (імена студентів) за алфавітом
  std::map<std::string, std::vector<int>> studentGrades;

  // Вставка даних у map
  // Оператор [] створює новий елемент з порожнім вектором, якщо ключ не існує
  // Потім присвоюємо йому список ініціалізації {85, 92, 78}
  studentGrades["Alice"] = {85, 92, 78};
  studentGrades["Bob"] = {90, 88, 91};
  studentGrades["Charlie"] = {70, 82, 89};

  // Отримання та виведення даних
  // Прохід по map: pair.first - ключ (ім'я), pair.second - значення (вектор оцінок)
  for (const auto &student : studentGrades) {
    std::cout << student.first << ": ";  // Виведення імені студента
    for (int grade : student.second) {   // Прохід по оцінках студента
      std::cout << grade << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}