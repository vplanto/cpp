// Демонстрація черги (Queue) у стандартній бібліотеці шаблонів (STL)
#include <iostream>
#include <queue>

using namespace std;

// Виведення черги
// Примітка: queue не має ітераторів, тому використовуємо копіювання та pop()
void showq(queue<int> gq) {
  queue<int> g = gq;  // Копія черги (queue передається за значенням)
  while (!g.empty()) {
    cout << '\t' << g.front();  // front() - доступ до першого елемента (FIFO)
    g.pop();                     // pop() - видалення першого елемента
  }
  cout << '\n';
}

int main() {
  queue<int> gquiz;
  gquiz.push(10);  // push() - додавання в кінець черги
  gquiz.push(20);
  gquiz.push(30);

  cout << "The queue gquiz is : ";
  showq(gquiz);

  cout << "\ngquiz.size() : " << gquiz.size();      // Розмір черги
  cout << "\ngquiz.front() : " << gquiz.front();    // Перший елемент
  cout << "\ngquiz.back() : " << gquiz.back();      // Останній елемент

  cout << "\ngquiz.pop() : ";
  gquiz.pop();  // Видалення першого елемента
  showq(gquiz);

  return 0;
}

