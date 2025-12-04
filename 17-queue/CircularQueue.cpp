// Включення всіх стандартних бібліотек
#include <bits/stdc++.h>
using namespace std;

// Клас циркулярної черги (Circular Queue)
// Переваги: ефективне використання пам'яті, O(1) для enqueue/dequeue
// Принцип: коли rear досягає кінця масиву, він "обертається" на початок
class Queue {
  int rear, front;  // rear - кінець, front - початок

  int size;  // Розмір черги
  int *arr;  // Масив для зберігання елементів

public:
  Queue(int s) {
    front = rear = -1;  // -1 означає порожню чергу
    size = s;
    arr = new int[s];
  }

  void enQueue(int value);
  int deQueue();
  void displayQueue();
};

// Функція додавання елемента в чергу
// Складність: O(1)
void Queue::enQueue(int value) {
  // Перевірка, чи черга заповнена
  // Дві умови: front на початку та rear в кінці, або rear+1 == front (обертання)
  if ((front == 0 && rear == size - 1) || ((rear + 1) % size == front)) {
    printf("\nQueue is Full");
    return;
  }

  // Якщо черга порожня
  else if (front == -1) {
    front = rear = 0;  // Вставка першого елемента
    arr[rear] = value;
  }

  // Якщо rear досяг кінця масиву, але front не на початку
  else if (rear == size - 1 && front != 0) {
    rear = 0;  // Обертання rear на початок масиву
    arr[rear] = value;
  }

  // Звичайний випадок
  else {
    rear++;
    arr[rear] = value;
  }
}

// Функція видалення елемента з черги
// Складність: O(1) - без зсуву елементів
int Queue::deQueue() {
  // Перевірка, чи черга порожня
  if (front == -1) {
    printf("\nQueue is Empty");
    return INT_MIN;
  }

  int data = arr[front];
  arr[front] = -1;  // Позначення видаленого елемента
  // Перевірка, чи черга має тільки один елемент
  if (front == rear) {
    front = -1;
    rear = -1;  // Черга стає порожньою
  } else if (front == size - 1)
    front = 0;  // Обертання front на початок масиву
  else
    front++;    // Звичайне збільшення front

  return data;
}

// Функція виведення елементів черги
void Queue::displayQueue() {
  if (front == -1) {
    printf("\nQueue is Empty");
    return;
  }
  printf("\nElements in Circular Queue are: ");
  // Якщо rear >= front, елементи в нормальному порядку
  if (rear >= front) {
    for (int i = front; i <= rear; i++)
      printf("%d ", arr[i]);
  } else {
    // Якщо rear < front, черга "обернулася" - виводимо дві частини
    for (int i = front; i < size; i++)
      printf("%d ", arr[i]);

    for (int i = 0; i <= rear; i++)
      printf("%d ", arr[i]);
  }
}

int main() {
  Queue q(5);

  q.enQueue(14);
  q.enQueue(22);
  q.enQueue(13);
  q.enQueue(-6);

  q.displayQueue();

  printf("\nDeleted value = %d", q.deQueue());
  printf("\nDeleted value = %d", q.deQueue());

  q.displayQueue();

  q.enQueue(9);
  q.enQueue(20);
  q.enQueue(5);

  q.displayQueue();

  q.enQueue(20);
  return 0;
}
