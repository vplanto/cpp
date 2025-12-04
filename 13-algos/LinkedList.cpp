#include <iostream>
#include <memory_resource>

// Шаблон вузла однозв'язаного списку
template <typename T> class Node {
public:
  T data;        // Дані вузла
  Node *next;    // Вказівник на наступний вузол

  Node(T data) : data(data), next(nullptr) {}
};

// Шаблон однозв'язаного списку
template <typename T> class LinkedList {
  Node<T> *head;  // Вказівник на голову списку
  int size;        // Розмір списку

public:
  LinkedList() : head(nullptr), size(0) {}

  ~LinkedList() { clear(); }  // Деструктор очищає список

  // Додавання елемента в список
  // position = -1 означає додавання в кінець
  // Складність: O(n) для вставки в позицію, O(1) для додавання в кінець
  void add(T data, int position = -1) {
    if ((position < 0) || (position > size)) {
      position = size;  // Якщо позиція некоректна, додаємо в кінець
    }
    Node<T> *current = head;
    if (current != nullptr) {
      int index = 0;
      // Прохід до позиції перед вставкою
      while (index != (position - 1)) {
        index++;
        current = current->next;
      }
      Node<T>* addNode=new Node<T>(data);
      auto temp = current->next;  // Зберігаємо наступний вузол
      current->next = addNode;    // Вставляємо новий вузол
      addNode->next = temp;       // З'єднуємо з наступним
    } else {
      head = new Node<T>(data);  // Якщо список порожній, створюємо голову
    }
    size++;
  }

  // Видалення елемента зі списку
  // position = -1 означає видалення останнього елемента
  // Складність: O(n) для видалення з позиції
  void remove(int position = -1) {
    if (head == nullptr) {
      std::cout << "List already empty.\n";
      return;
    }

    if ((position < 0) || (position > size)) {
      position = size;  // Якщо позиція некоректна, видаляємо останній
    }

    if (size == 1) {
      delete head;
      head = nullptr;
      size--;
      return;
    }

    if (position == 0) {
      auto temp = head->next;
      delete head;
      head = temp;  // Оновлюємо голову
      size--;
      return;
    }
    Node<T> *current = head;
    int index = 0;
    // Прохід до вузла перед тим, що видаляємо
    for (int index = 0; index < position - 1; ++index) {
      index++;
      current = current->next;
    }

    auto temp = current->next->next;  // Зберігаємо вказівник на вузол після видаленого

    delete current->next;  // Видаляємо вузол
    current->next = temp;  // Оновлюємо зв'язок
    size--;
  }

  // Очищення всього списку
  // Складність: O(n)
  void clear() {
    Node<T> *current = head;
    while (current != nullptr) {
      auto temp = current->next;  // Зберігаємо наступний перед видаленням
      delete current;
      current = temp;
    }
    head = nullptr;
    size = 0;
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
