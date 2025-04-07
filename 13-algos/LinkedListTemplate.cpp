#include <iostream>

template <typename T> class Node {
public:
  T data;
  Node *next;

  Node(T data) : data(data), next(nullptr) {}
};

template <typename T> class LinkedList {
  Node<T> *head;
  int size;

public:
  LinkedList() : head(nullptr), size(0) {}

  ~LinkedList() { clear(); }

  void add(T data, int position = -1) {
//TODO implement add
  }

  void remove(int position = -1) {
//TODO implement remove
  }

  void clear() {
    while (head != nullptr) {
      remove();
    }
  }

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
  myList.add(3, 1); // List becomes: 1 3 2
  myList.print();

  myList.remove(); // List becomes: 3 2
  myList.print();

  myList.remove(0); // List becomes: 2
  myList.print();

  myList.clear(); // List becomes:
  myList.print();

  return 0;
}

