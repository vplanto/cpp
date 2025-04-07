#include <forward_list>
#include <iostream>

class MyList {
private:
  std::forward_list<int> flist;

public:
  void add(int value, int position = -1) {
    if (position == -1) {
      flist.push_front(value);
    } else {
      auto it = flist.begin();
      std::advance(it, position);
      flist.insert_after(it, value);
    }
  }

  void remove(int position = 0) {
    if (position == 0) {
      flist.pop_front();
    } else {
      auto it = flist.begin();
      std::advance(it, position - 1);
      flist.erase_after(it);
    }
  }

  void clear() { flist.clear(); }

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

