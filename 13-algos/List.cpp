#include <iostream>

// Динамічний масив (аналог vector) з автоматичним збільшенням
template <typename T> class List {
  T *arr;        // Динамічний масив
  int capacity;  // Місткість масиву
  int size;      // Поточна кількість елементів

public:
  List(int capacity = 2) : capacity(capacity), size(0) {
    arr = new T[capacity];  // Виділення початкової пам'яті
  }

  ~List() { delete[] arr; }  // Звільнення пам'яті

  // Збільшення місткості масиву (подвоєння)
  // Складність: O(n) - копіювання всіх елементів
  void resize() {
    T *newArr = new T[capacity * 2];  // Новий масив подвійного розміру
    for (int i = 0; i < size; i++) {
      newArr[i] = arr[i];  // Копіювання елементів
    }
    delete[] arr;  // Звільнення старого масиву
    capacity *= 2;
    arr = newArr;
  }

  // Додавання елемента в список
  // position = -1 означає додавання в кінець
  // Складність: O(1) для додавання в кінець, O(n) для вставки в позицію
  void add(T value, int position = -1) {
    if (position > size || position < -1) {
      position = -1;
    }
    if (size == capacity)
      resize();  // Автоматичне збільшення при заповненні

    if (position == -1) {
      arr[size] = value;  // Додавання в кінець (O(1))
      size++;
    } else {
      // Зсув елементів вправо для вставки
      for (int i = size; i > position; i--) {
        arr[i] = arr[i - 1];
      }
      size++;
      arr[position] = value;  // Вставка нового елемента
    }
  }

  // Видалення елемента зі списку
  // position = -1 означає видалення останнього елемента
  // Складність: O(1) для видалення з кінця, O(n) для видалення з позиції
  void remove(int position = -1) {
    if (position > size || position < -1) {
      position = -1;
    }

    if (capacity == 0) {
      // Помилка: порожній список
    } else {
      if (position == -1) {
        size--;  // Видалення з кінця (O(1))
      } else {
        // Зсув елементів вліво для видалення
        for (int i = position; i < (size - 1); i++) {
          arr[i] = arr[i + 1];
        }
        size--;
      }
    }
  }

  // Очищення списку (зберігає місткість)
  void clear() {
    delete[] arr;
    arr = new T[capacity];  // Виділення нового масиву з тією ж місткістю
    size = 0;
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
  myList.add(3, 1); // Список стає: 1 3 2
  myList.print();

  myList.remove(); // Список стає: 1 3
  myList.print();

  myList.remove(0); // Список стає: 3
  myList.print();

  myList.clear(); // Список стає порожнім
  myList.print();

  return 0;
}
