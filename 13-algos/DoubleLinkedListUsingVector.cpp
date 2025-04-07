#include <iostream>
#include <list>
#include <vector>

// Function to print the contents of a container
template <typename T> void printContainer(const T &container) {
  for (const auto &element : container) {
    std::cout << element << ' ';
  }
  std::cout << '\n';
}

int main() {
  // For std::vector
  std::vector<int> vec = {1, 2, 3, 4, 5};

  // Add to the end
  vec.push_back(6);
  std::cout << "Vector after adding to the end: ";
  printContainer(vec);

  // Add to a position (insert 7 at the 3rd position)
  vec.insert(vec.begin() + 2, 7);
  std::cout << "Vector after adding to the position: ";
  printContainer(vec);

  // Delete from the end
  vec.pop_back();
  std::cout << "Vector after deleting from the end: ";
  printContainer(vec);

  // Delete from a position (delete 3rd element)
  vec.erase(vec.begin() + 2);
  std::cout << "Vector after deleting from the position: ";
  printContainer(vec);

  // For std::list
  std::list<int> lst = {1, 2, 3, 4, 5};

  // Add to the end
  lst.push_back(6);
  std::cout << "List after adding to the end: ";
  printContainer(lst);

  // Add to a position (insert 7 at the 3rd position)
  auto it = lst.begin();
  std::advance(it, 2);
  lst.insert(it, 7);
  std::cout << "List after adding to the position: ";
  printContainer(lst);

  // Delete from the end
  lst.pop_back();
  std::cout << "List after deleting from the end: ";
  printContainer(lst);

  // Delete from a position (delete 3rd element)
  it = lst.begin();
  std::advance(it, 2);
  lst.erase(it);
  std::cout << "List after deleting from the position: ";
  printContainer(lst);

  return 0;
}

