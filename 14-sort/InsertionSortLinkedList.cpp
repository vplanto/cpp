#include <iostream>
using namespace std;

struct Node {
  int data;
  struct Node *next;
};
//Node node - object
//*node - reference to object
//**node - reference to reference to object
void push(Node **head_ref, int new_data) {
  Node *new_node = new Node;
  new_node->data = new_data;
  new_node->next = (*head_ref);
  (*head_ref) = new_node;
}

void sortedInsert(struct Node **, struct Node *);

void insertionSort(struct Node **head_ref) {
  struct Node *sorted = NULL;

  struct Node *current = *head_ref;
  while (current != NULL) {
    struct Node *next = current->next;

    sortedInsert(&sorted, current);

    current = next;
  }

  *head_ref = sorted;
}

void sortedInsert(Node **head_ref, Node *new_node) {
  Node *current;
  if (*head_ref == NULL || (*head_ref)->data >= new_node->data) {
    new_node->next = *head_ref;
    *head_ref = new_node;
  } else {
    current = *head_ref;
    while (current->next != NULL && current->next->data < new_node->data) {
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
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
