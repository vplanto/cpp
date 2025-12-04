/* Програма для реалізації стеку за допомогою двох черг */
#include <bits/stdc++.h>

using namespace std;

// Клас стеку, реалізований за допомогою двох черг
// Принцип: q1 містить елементи стеку, q2 використовується для перестановки
// Складність push(): O(n), pop(): O(1)
class Stack {
  // Дві вбудовані черги
  queue<int> q1, q2;  // q1 - основна черга, q2 - допоміжна

public:
  void push(int x) {
    // Спочатку додаємо x в порожню q2
    q2.push(x);

    // Переміщуємо всі елементи з q1 в q2
    // Це забезпечує, що новий елемент буде на початку q2
    while (!q1.empty()) {
      q2.push(q1.front());
      q1.pop();
    }

    // Обмін імен двох черг (q1 стає q2, q2 стає порожньою)
    queue<int> q = q1;
    q1 = q2;
    q2 = q;
  }

  void pop() {
    // Якщо немає елементів у q1
    if (q1.empty())
      return;
    q1.pop();  // Видалення з початку q1 (верх стеку)
  }

  int top() {
    if (q1.empty())
      return -1;
    return q1.front();  // Перший елемент q1 - верх стеку
  }

  int size() { return q1.size(); }
};

int main() {
  Stack s;
  s.push(1);
  s.push(2);
  s.push(3);

  cout << "current size: " << s.size() << endl;
  cout << s.top() << endl;
  s.pop();
  cout << s.top() << endl;
  s.pop();
  cout << s.top() << endl;

  cout << "current size: " << s.size() << endl;
  return 0;
}
