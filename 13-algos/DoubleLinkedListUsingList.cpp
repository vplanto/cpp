#include <iostream>
#include <list>

class MyList {
private:
  std::list<int> list;

public:
  void add(int value, int position = -1) {
    if (position == -1) {
      list.push_front(value);
    } else {
      auto it = list.begin();
      std::advance(it, position);//Has O(n) complexity
      list.insert(it, value);
    }
  }

  void remove(int position = 0) {
    if (position == 0) {
      list.pop_front();
    } else {
      auto it = list.begin();
      std::advance(it, position);
      list.erase(it);
    }
  }

  void clear() { list.clear(); }

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

