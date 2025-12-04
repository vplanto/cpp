#include <forward_list>  // Стандартний однозв'язаний список
#include <iostream>

// Обгортка над std::forward_list для демонстрації роботи з однозв'язаним списком
class MyList {
private:
  std::forward_list<int> flist;  // Однозв'язаний список (тільки вперед)

public:
  // Додавання елемента в список
  // forward_list не має push_back(), тільки push_front() та insert_after()
  void add(int value, int position = -1) {
    if (position == -1) {
      flist.push_front(value);  // Додавання на початок (O(1))
    } else {
      auto it = flist.begin();
      std::advance(it, position);  // Переміщення ітератора (O(n))
      flist.insert_after(it, value);  // Вставка після позиції
    }
  }

  // Видалення елемента зі списку
  // forward_list має pop_front() та erase_after()
  void remove(int position = 0) {
    if (position == 0) {
      flist.pop_front();  // Видалення з початку (O(1))
    } else {
      auto it = flist.begin();
      std::advance(it, position - 1);  // Переміщення до елемента перед тим, що видаляємо
      flist.erase_after(it);  // Видалення після позиції
    }
  }

  void clear() { flist.clear(); }  // Очищення списку

  // Виведення вмісту через range-based for loop
  void print() {
    for (const auto &value : flist) {
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

