// C++ програма для реалізації стеку за допомогою deque (double-ended queue)
#include <bits/stdc++.h>
using namespace std;

// Клас стеку, реалізований за допомогою deque
// deque дозволяє ефективні операції на обох кінцях (O(1))
class Stack {
private:
  deque<int> my_deque;  // Двобічна черга (double-ended queue)

public:
  void push(int item) {
    // Додавання елемента в кінець deque
    my_deque.push_back(item);  // O(1)
  }

  int pop() {
    // Видалення та повернення елемента з кінця deque
    int item = my_deque.back();  // Отримання останнього елемента
    my_deque.pop_back();         // Видалення останнього елемента
    return item;                 // O(1)
  }

  int size() {
    return my_deque.size();
  }

  bool is_empty() {
    return my_deque.empty();
  }

  int top() {
    if (is_empty()) {
      return -1;
    } else {
      return my_deque.back();  // Повернення останнього елемента без видалення
    }
  }
};

int main() {
  Stack st;
  st.push(1);
  st.push(2);
  st.push(3);
  cout << "current size: " << st.size() << endl;
  cout << st.top() << endl;
  st.pop();
  cout << st.top() << endl;
  st.pop();
  cout << st.top() << endl;
  cout << "current size: " << st.size() << endl;
  return 0;
}
