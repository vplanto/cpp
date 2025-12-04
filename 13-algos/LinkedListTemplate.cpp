#include <iostream>

// Шаблон вузла однозв'язаного списку
template <typename T> class Node {
public:
  T data;        // Дані вузла
  Node *next;    // Вказівник на наступний вузол

  Node(T data) : data(data), next(nullptr) {}
};

// Шаблон однозв'язаного списку (заготовка для реалізації)
template <typename T> class LinkedList {
  Node<T> *head;  // Вказівник на голову списку
  int size;        // Розмір списку

public:
  LinkedList() : head(nullptr), size(0) {}

  ~LinkedList() { clear(); }

  // TODO: Реалізувати додавання елемента в список
  // position = -1 означає додавання в кінець
  void add(T data, int position = -1) {
//TODO implement add
  }

  // TODO: Реалізувати видалення елемента зі списку
  // position = -1 означає видалення останнього елемента
  void remove(int position = -1) {
//TODO implement remove
  }

  // Очищення всього списку (використовує remove())
  void clear() {
    while (head != nullptr) {
      remove();
    }
  }

  // Виведення вмісту списку
  void print() {
    Node<T> *current = head;
    while (current != nullptr) {
      std::cout << current->data << ' ';
      current = current->next;
    }
    std::cout << '\n';
  }
};

int main() {
  LinkedList<int> myList;

  myList.add(1);
  myList.add(2);
  myList.add(3, 1); // Список має стати: 1 3 2
  myList.print();

  myList.remove(); // Список має стати: 3 2
  myList.print();

  myList.remove(0); // Список має стати: 2
  myList.print();

  myList.clear(); // Список має стати порожнім
  myList.print();

  return 0;
}

