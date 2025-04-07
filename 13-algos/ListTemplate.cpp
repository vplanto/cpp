#include <iostream>

template <typename T> class List {
  T *arr;
  int capacity;
  int size;

public:
  List(int capacity = 2) : capacity(capacity), size(0) {
    arr = new T[capacity];
  }

  ~List() { delete[] arr; }

  void resize() {
//TODO implement resize
  }

  void add(T value, int position = -1) {
//TODO impletement add
  }

  void remove(int position = -1) {
//TODO implement remove
  }

  void clear() {
    delete[] arr;
    capacity = 2;
    size = 0;
    arr = new T[capacity];
  }

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
  myList.add(3, 1); // List becomes: 1 3 2
  myList.print();

  myList.remove(); // List becomes: 1 3
  myList.print();

  myList.remove(0); // List becomes: 3
  myList.print();

  myList.clear(); // List becomes:
  myList.print();

  return 0;
}
