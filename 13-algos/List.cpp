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
    T *newArr = new T[capacity * 2];
    for (int i = 0; i < size; i++) {
      newArr[i] = arr[i];
    }
    delete[] arr;
    capacity *= 2;
    arr = newArr;
  }

  void add(T value, int position = -1) {
    // to implement adding new value
    if (position > size || position < -1) {
      position = -1;
    }
    if (size == capacity)
      resize();

    if (position == -1) {
      arr[size] = value;
      size++;
    } else {
      for (int i = size; i > position; i--) {
        arr[i] = arr[i - 1];
      }
      size++;
      arr[position] = value;
    }
  }

  void remove(int position = -1) {
    // to implement removing value
    if (position > size || position < -1) {
      position = -1;
    }

    if (capacity == 0) {
      // raise error
    } else {
      if (position == -1) {
        size--;
      } else {
        for (int i = position; i < (size - 1); i++) {
          arr[i] = arr[i + 1];
        }
        size--;
      }
    }
  }

  void clear() {
    // to implement clearing the list
    delete[] arr;
    arr = new T[capacity];
    size = 0;
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
