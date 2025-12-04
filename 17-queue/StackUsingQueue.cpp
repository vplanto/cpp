#include <bits/stdc++.h>
using namespace std;

// Клас стеку, реалізований за допомогою однієї черги
// Принцип: при push() переставляємо всі елементи, щоб новий був на початку
// Складність push(): O(n), pop(): O(1)
class Stack {

  queue<int> q;  // Одна черга для реалізації стеку

public:
  void push(int data);
  void pop();
  int top();
  int size();
  bool empty();
};

// Операція push (додавання елемента)
// НЕЕФЕКТИВНО: O(n) через перестановку всіх елементів
void Stack::push(int data) {
  int s = q.size();  // Зберігаємо попередній розмір черги

  q.push(data);  // Додаємо новий елемент в кінець черги

  // Переставляємо всі попередні елементи після нового
  // Це забезпечує поведінку стеку (LIFO)
  for (int i = 0; i < s; i++) {
    q.push(q.front());  // Додаємо front елемент знову в кінець
    q.pop();            // Видаляємо front елемент
  }
}

// Видалення верхнього елемента
void Stack::pop() {
  if (q.empty())
    cout << "No elements\n";
  else
    q.pop();  // Видалення з початку черги (який є верхом стеку)
}

// Повернення верхнього елемента стеку
int Stack::top() { return (q.empty()) ? -1 : q.front(); }

// Перевірка, чи стек порожній
bool Stack::empty() { return (q.empty()); }

int Stack::size() { return q.size(); }

int main() {
  Stack st;
  st.push(1);
  st.push(2);
  st.push(3);
  cout << "current size: " << st.size() << "\n";
  cout << st.top() << "\n";
  st.pop();
  cout << st.top() << "\n";
  st.pop();
  cout << st.top() << "\n";
  cout << "current size: " << st.size();
  return 0;
}
