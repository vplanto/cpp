#include <iostream>
#include <list>    // Двозв'язаний список
#include <vector>  // Динамічний масив

// Шаблонна функція для виведення вмісту контейнера
template <typename T> void printContainer(const T &container) {
  for (const auto &element : container) {
    std::cout << element << ' ';
  }
  std::cout << '\n';
}

int main() {
  // Робота з std::vector (динамічний масив)
  std::vector<int> vec = {1, 2, 3, 4, 5};

  // Додавання в кінець
  vec.push_back(6);  // O(1) амортизовано, O(n) при перевиділенні
  std::cout << "Vector after adding to the end: ";
  printContainer(vec);

  // Додавання в позицію (вставка 7 на 3-тю позицію)
  vec.insert(vec.begin() + 2, 7);  // O(n) - зсув елементів
  std::cout << "Vector after adding to the position: ";
  printContainer(vec);

  // Видалення з кінця
  vec.pop_back();  // O(1)
  std::cout << "Vector after deleting from the end: ";
  printContainer(vec);

  // Видалення з позиції (видалення 3-го елемента)
  vec.erase(vec.begin() + 2);  // O(n) - зсув елементів
  std::cout << "Vector after deleting from the position: ";
  printContainer(vec);

  // Робота з std::list (двозв'язаний список)
  std::list<int> lst = {1, 2, 3, 4, 5};

  // Додавання в кінець
  lst.push_back(6);  // O(1)
  std::cout << "List after adding to the end: ";
  printContainer(lst);

  // Додавання в позицію (вставка 7 на 3-тю позицію)
  auto it = lst.begin();
  std::advance(it, 2);  // O(n) - прохід до позиції
  lst.insert(it, 7);   // O(1) після досягнення позиції
  std::cout << "List after adding to the position: ";
  printContainer(lst);

  // Видалення з кінця
  lst.pop_back();  // O(1)
  std::cout << "List after deleting from the end: ";
  printContainer(lst);

  // Видалення з позиції (видалення 3-го елемента)
  it = lst.begin();
  std::advance(it, 2);  // O(n) - прохід до позиції
  lst.erase(it);        // O(1) після досягнення позиції
  std::cout << "List after deleting from the position: ";
  printContainer(lst);

  return 0;
}

