#include <iostream>

// Динамічний масив (аналог vector) - заготовка для реалізації
template <typename T> class List {
  T *arr;        // Динамічний масив
  int capacity;  // Місткість масиву
  int size;      // Поточна кількість елементів

public:
  List(int capacity = 2) : capacity(capacity), size(0) {
    arr = new T[capacity];
  }

  ~List() { delete[] arr; }

  // TODO: Реалізувати збільшення місткості масиву (подвоєння)
  // Складність: O(n) - копіювання всіх елементів
  void resize() {
//TODO implement resize
  }

  // TODO: Реалізувати додавання елемента
  // position = -1 означає додавання в кінець
  void add(T value, int position = -1) {
//TODO impletement add
  }

  // TODO: Реалізувати видалення елемента
  // position = -1 означає видалення останнього елемента
  void remove(int position = -1) {
//TODO implement remove
  }

  // Очищення списку (зберігає місткість)
  void clear() {
    delete[] arr;
    capacity = 2;
    size = 0;
    arr = new T[capacity];
  }

  // Виведення вмісту списку
  void print() {
    for (int i = 0; i < size; i++) {
      std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
  }
};

int main() {
  List<int> myList;

  myList.add(1);
  myList.add(2);
  myList.add(3, 1); // Список має стати: 1 3 2
  myList.print();

  myList.remove(); // Список має стати: 1 3
  myList.print();

  myList.remove(0); // Список має стати: 3
  myList.print();

  myList.clear(); // Список має стати порожнім
  myList.print();

  return 0;
}
