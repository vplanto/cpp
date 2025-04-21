#include <iostream>
#include <memory_resource>

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
    if ((position < 0) || (position > size)) {
      position = size;
    }
    Node<T> *current = head;
    if (current != nullptr) {
      int index = 0;
      while (index != (position - 1)) {
        index++;
        current = current->next;
      }
      Node<T>* addNode=new Node<T>(data);
      auto temp = current->next;
      current->next = addNode;
      addNode->next = temp;
    } else {
      head= new Node<T>(data);
    }
    size++;
  }

  void remove(int position = -1) {
    if (head == nullptr) {
      std::cout << "List already empty.\n";
      return;
    }

    if ((position < 0) || (position > size)) {
      position = size;
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
      head = temp;
      size--;
      return;
    }
    Node<T> *current = head;
    int index = 0;
    for (int index = 0; index < position - 1; ++index) {
      index++;
      current = current->next;
    }

    auto temp = current->next->next;

    delete current->next;
    current->next = temp;
    size--;
  }

  void clear() {
    Node<T> *current = head;
    while (current != nullptr) {
      auto temp = current->next;
      delete current;
      current = temp;
    }
    head = nullptr;
    size = 0;
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
