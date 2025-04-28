// Include all standard library headers
#include <bits/stdc++.h>
// Use the standard namespace
using namespace std;

// Define a class named Queue
class Queue {
  // Declare private variables: rear, front
  int rear, front;

  // Declare private variables: size, arr
  int size;
  int *arr;

public:
  // Constructor for the Queue class
  Queue(int s) {
    // Initialize front and rear to -1
    front = rear = -1;
    // Set the size of the queue
    size = s;
    // Allocate memory for the queue
    arr = new int[s];
  }

  // Declare public member functions
  void enQueue(int value);
  int deQueue();
  void displayQueue();
};

// Define the enQueue function
void Queue::enQueue(int value) {
  // Check if the queue is full
  if ((front == 0 && rear == size - 1) || ((rear + 1) % size == front)) {
    // Print a message and return
    printf("\nQueue is Full");
    return;
  }

  // Check if the queue is empty
  else if (front == -1) {
    // Insert the first element
    front = rear = 0;
    arr[rear] = value;
  }

  // Check if the rear has reached the end of the array
  else if (rear == size - 1 && front != 0) {
    // Wrap around the rear to the beginning of the array
    rear = 0;
    arr[rear] = value;
  }

  // If none of the above conditions are met
  else {
    // Increment the rear and insert the value
    rear++;
    arr[rear] = value;
  }
}

// Define the deQueue function
int Queue::deQueue() {
  // Check if the queue is empty
  if (front == -1) {
    // Print a message and return INT_MIN
    printf("\nQueue is Empty");
    return INT_MIN;
  }

  // Store the front element in a variable
  int data = arr[front];
  // Mark the front element as deleted
  arr[front] = -1;
  // Check if the queue has only one element
  if (front == rear) {
    // Reset the front and rear to -1
    front = -1;
    rear = -1;
  } else if (front == size - 1)
    // Wrap around the front to the beginning of the array
    front = 0;
  else
    // Increment the front
    front++;

  // Return the deleted element
  return data;
}

// Define the displayQueue function
void Queue::displayQueue() {
  // Check if the queue is empty
  if (front == -1) {
    // Print a message and return
    printf("\nQueue is Empty");
    return;
  }
  // Print the elements in the queue
  printf("\nElements in Circular Queue are: ");
  // Check if the rear is greater than or equal to the front
  if (rear >= front) {
    // Print the elements from front to rear
    for (int i = front; i <= rear; i++)
      printf("%d ", arr[i]);
  } else {
    // Print the elements from front to the end of the array
    for (int i = front; i < size; i++)
      printf("%d ", arr[i]);

    // Print the elements from the beginning of the array to the rear
    for (int i = 0; i <= rear; i++)
      printf("%d ", arr[i]);
  }
}

// Define the main function
int main() {
  // Create a Queue object with size 5
  Queue q(5);

  // Insert elements into the queue
  q.enQueue(14);
  q.enQueue(22);
  q.enQueue(13);
  q.enQueue(-6);

  // Display the elements in the queue
  q.displayQueue();

  // Delete elements from the queue
  printf("\nDeleted value = %d", q.deQueue());
  printf("\nDeleted value = %d", q.deQueue());

  // Display the elements in the queue
  q.displayQueue();

  // Insert more elements into the queue
  q.enQueue(9);
  q.enQueue(20);
  q.enQueue(5);

  // Display the elements in the queue
  q.displayQueue();

  // Insert another element into the queue
  q.enQueue(20);
  // End of the main function
  return 0;
}
