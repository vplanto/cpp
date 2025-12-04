/* Тестування шаблону класу vector (TestVectorTemplate.cpp) */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Animal {
  string color;
};

int main() {
  // vector<Animal> - шаблон класу vector інстанційований для типу Animal
  vector<Animal> v0;
  v0.push_back({"red"});  // Додавання елемента через список ініціалізації

  vector<int> v1(5);  // Створення vector з 5 елементами (ініціалізовані значенням за замовчуванням)

  // Присвоєння значень у v1, використовуючи індекс []
  // size() - отримання розміру vector
  for (int i = 0; i < v1.size(); ++i) {
    v1[i] = (i + 1) * 2;  // [] - без перевірки меж індексу
  }

  // Виведення вмісту vector, використовуючи at()
  for (int i = 0; i < v1.size(); ++i) {
    cout << v1.at(i) << " ";  // at() - з перевіркою меж індексу (викидає виняток)
  }
  cout << endl;

  vector<int> v2;  // Створення vector з 0 елементами
  // Присвоєння v1 до v2 (поелементне копіювання)
  v2 = v1;  // Оператор присвоєння копіювання
  for (int i = 0; i < v2.size(); ++i) {
    cout << v2[i] << " ";
  }
  cout << endl;

  // Порівняння двох vector (поелементне)
  cout << boolalpha << (v1 == v2) << endl;  // Оператор == для vector

  // Додавання елементів - динамічне виділення пам'яті
  v1.push_back(80);  // push_back - додавання в кінець
  v1.push_back(81);
  for (int i = 0; i < v1.size(); ++i) {
    cout << v1[i] << " ";
  }
  cout << endl;

  // Видалення елемента з кінця
  v1.pop_back();  // pop_back - видалення останнього елемента
  for (int i = 0; i < v1.size(); ++i) {
    cout << v1[i] << " ";
  }
  cout << endl;

  vector<string> v3;            // Створення vector рядків з 0 елементами
  v3.push_back("A for Apple");  // Додавання нових елементів
  v3.push_back("B for Boy");
  for (int i = 0; i < v3.size(); ++i) {
    cout << v3[i] << " ";
  }
  cout << endl;
}
