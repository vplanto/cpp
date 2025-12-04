#include <iostream>
#include <list>  // Стандартний двозв'язаний список

// Обгортка над std::list для демонстрації роботи з двозв'язаним списком
class MyList {
private:
  std::list<int> list;  // Двозв'язаний список (можна рухатися в обидва боки)

public:
  // Додавання елемента в список
  // std::list підтримує вставку в будь-яку позицію
  void add(int value, int position = -1) {
    if (position == -1) {
      list.push_front(value);  // Додавання на початок (O(1))
    } else {
      auto it = list.begin();
      std::advance(it, position);  // Переміщення ітератора (O(n) складність)
      list.insert(it, value);     // Вставка в позицію (O(1) після досягнення позиції)
    }
  }

  // Видалення елемента зі списку
  void remove(int position = 0) {
    if (position == 0) {
      list.pop_front();  // Видалення з початку (O(1))
    } else {
      auto it = list.begin();
      std::advance(it, position);  // Переміщення до позиції (O(n))
      list.erase(it);             // Видалення (O(1) після досягнення позиції)
    }
  }

  void clear() { list.clear(); }  // Очищення списку

  // Виведення вмісту через range-based for loop
  void print() {
    for (const auto &value : list) {
      std::cout << value << " ";
    }
    std::cout << std::endl;
  }
};

int main() {
  MyList myList;

  myList.add(1);
  myList.add(2);
  myList.add(3, 1); // Список стає: 1 3 2
  myList.print();

  myList.remove(); // Список стає: 3 2
  myList.print();

  myList.remove(0); // Список стає: 2
  myList.print();

  myList.clear(); // Список стає порожнім
  myList.print();

  return 0;
}

