// C++ program to implement a queue using an array
#include <bits/stdc++.h>
using namespace std;

struct Queue {
  int front, rear, capacity;
  int *queue;
  Queue(int c) {
    front = rear = 0;
    capacity = c;
    queue = new int[c];
  }

  ~Queue() { delete[] queue; }

  // function to insert an element
  // at the rear of the queue
  void queueEnqueue(int data) {
    // check queue is full or not
    if (capacity == rear) {
      printf("\nQueue is full\n");
      return;
    }

    // insert element at the rear
    else {
      queue[rear] = data;
      rear++;
    }
    return;
  }

  // function to delete an element
  // from the front of the queue
  void queueDequeue() {
    // if queue is empty
    if (front == rear) {
      printf("\nQueue is  empty\n");
      return;
    }

    // shift all the elements from index 2 till rear
    // to the left by one
    else {
      for (int i = 0; i < rear - 1; i++) {
        queue[i] = queue[i + 1];
      }

      // decrement rear
      rear--;
    }
    return;
  }

  // print queue elements
  void queueDisplay() {
    int i;
    if (front == rear) {
      printf("\nQueue is Empty\n");
      return;
    }

    // traverse front to rear and print elements
    for (i = front; i < rear; i++) {
      printf(" %d <-- ", queue[i]);
    }
    return;
  }

  // print front of queue
  void queueFront() {
    if (front == rear) {
      printf("\nQueue is Empty\n");
      return;
    }
    printf("\nFront Element is: %d", queue[front]);
    return;
  }
};

// Driver code
int main(void) {
  // Create a queue of capacity 4
  Queue q(4);

  // print Queue elements
  q.queueDisplay();

  // inserting elements in the queue
  q.queueEnqueue(20);
  q.queueEnqueue(30);
  q.queueEnqueue(40);
  q.queueEnqueue(50);

  // print Queue elements
  q.queueDisplay();

  // insert element in the queue
  q.queueEnqueue(60);

  // print Queue elements
  q.queueDisplay();

  q.queueDequeue();
  q.queueDequeue();

  printf("\n\nafter two node deletion\n\n");

  // print Queue elements
  q.queueDisplay();

  // print front of the queue
  q.queueFront();

  return 0;
}
