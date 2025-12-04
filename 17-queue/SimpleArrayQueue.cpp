// C++ програма для реалізації черги за допомогою масиву
#include <bits/stdc++.h>
using namespace std;

// Проста реалізація черги на масиві (неефективна через зсув елементів)
struct Queue {
  int front, rear, capacity;
  int *queue;
  Queue(int c) {
    front = rear = 0;  // front та rear починаються з 0
    capacity = c;
    queue = new int[c];
  }

  ~Queue() { delete[] queue; }

  // Функція вставки елемента в кінець черги
  // Складність: O(1)
  void queueEnqueue(int data) {
    // Перевірка, чи черга заповнена
    if (capacity == rear) {
      printf("\nQueue is full\n");
      return;
    }

    // Вставка елемента в кінець
    else {
      queue[rear] = data;
      rear++;
    }
    return;
  }

  // Функція видалення елемента з початку черги
  // НЕЕФЕКТИВНО: O(n) через зсув всіх елементів
  void queueDequeue() {
    // Якщо черга порожня
    if (front == rear) {
      printf("\nQueue is  empty\n");
      return;
    }

    // Зсув всіх елементів від індексу 2 до rear вліво на одну позицію
    // Це неефективно - краще використовувати циркулярну чергу
    else {
      for (int i = 0; i < rear - 1; i++) {
        queue[i] = queue[i + 1];
      }

      // Зменшення rear
      rear--;
    }
    return;
  }

  // Виведення елементів черги
  void queueDisplay() {
    int i;
    if (front == rear) {
      printf("\nQueue is Empty\n");
      return;
    }

    // Прохід від front до rear та виведення елементів
    for (i = front; i < rear; i++) {
      printf(" %d <-- ", queue[i]);
    }
    return;
  }

  // Виведення першого елемента черги
  void queueFront() {
    if (front == rear) {
      printf("\nQueue is Empty\n");
      return;
    }
    printf("\nFront Element is: %d", queue[front]);
    return;
  }
};

int main(void) {
  // Створення черги місткістю 4
  Queue q(4);

  q.queueDisplay();

  // Вставка елементів у чергу
  q.queueEnqueue(20);
  q.queueEnqueue(30);
  q.queueEnqueue(40);
  q.queueEnqueue(50);

  q.queueDisplay();

  // Спроба вставки елемента (черга заповнена)
  q.queueEnqueue(60);

  q.queueDisplay();

  q.queueDequeue();
  q.queueDequeue();

  printf("\n\nafter two node deletion\n\n");

  q.queueDisplay();

  q.queueFront();

  return 0;
}
