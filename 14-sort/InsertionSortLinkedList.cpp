#include <iostream>
using namespace std;

struct Node {
  int data;
  struct Node *next;
};

// Примітки про вказівники:
// Node node - об'єкт
// *node - вказівник на об'єкт
// **node - вказівник на вказівник на об'єкт

// Додавання елемента на початок списку
// head_ref - вказівник на вказівник (для зміни голови списку)
void push(Node **head_ref, int new_data) {
  Node *new_node = new Node;
  new_node->data = new_data;
  new_node->next = (*head_ref);  // Новий вузол вказує на стару голову
  (*head_ref) = new_node;        // Оновлення голови списку
}

void sortedInsert(struct Node **, struct Node *);

// Сортування вставками для зв'язаного списку
// Алгоритм: створюємо новий відсортований список, вставляючи елементи в правильну позицію
// Складність: O(n²) у найгіршому випадку
void insertionSort(struct Node **head_ref) {
  struct Node *sorted = NULL;  // Новий відсортований список

  struct Node *current = *head_ref;
  while (current != NULL) {
    struct Node *next = current->next;  // Зберігаємо наступний вузол

    sortedInsert(&sorted, current);  // Вставка поточного вузла в відсортований список

    current = next;  // Перехід до наступного вузла
  }

  *head_ref = sorted;  // Оновлення голови списку
}

// Вставка вузла в відсортований список у правильну позицію
void sortedInsert(Node **head_ref, Node *new_node) {
  Node *current;
  // Якщо список порожній або новий елемент менший за голову
  if (*head_ref == NULL || (*head_ref)->data >= new_node->data) {
    new_node->next = *head_ref;
    *head_ref = new_node;  // Новий елемент стає головою
  } else {
    // Пошук правильної позиції для вставки
    current = *head_ref;
    while (current->next != NULL && current->next->data < new_node->data) {
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;  // Вставка після current
  }
}

void printList(struct Node *head) {
  while (head != NULL) {
    cout << head->data << " ";
    head = head->next;
  }
}

int main() {
  struct Node *a = NULL;
  push(&a, 5);
  push(&a, 20);
  push(&a, 4);
  push(&a, 3);
  push(&a, 30);
  //{30,3,4,20,5}
  cout << "Linked List before sorting \n";
  printList(a);

  insertionSort(&a);

  cout << "\nLinked List after sorting \n";
  printList(a);

  return 0;
}
