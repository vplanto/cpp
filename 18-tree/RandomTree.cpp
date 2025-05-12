#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tNode {
  int data;
  struct tNode *left;
  struct tNode *right;
};

// Function to create a new node
struct tNode *newNode(int data) {
  struct tNode *node = (struct tNode *)malloc(sizeof(struct tNode));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return (node);
}

// Function to insert a new node in BST
struct tNode *insert(struct tNode *node, int data) {
  if (node == NULL)
    return (newNode(data));
  else {
    if (data <= node->data)
      node->left = insert(node->left, data);
    else
      node->right = insert(node->right, data);
    return (node);
  }
}

// Function for in-order tree traversal
void printInorder(struct tNode *node) {
  if (node == NULL)
    return;
  printInorder(node->left);
  // printf("%d ", node->data);
  printInorder(node->right);
}

int main() {
  struct tNode *root = NULL;
  srand(time(0)); // Use current time as seed for random generator

  // Ask user for number of records to create
  int num_records;
  printf("Enter the number of records to create: ");
  if (scanf("%d", &num_records) != 1) {
    fprintf(stderr, "Error reading input\n");
    return 1;
  }

  // Create random records
  for (int i = 0; i < num_records; i++) {
    root = insert(root, rand() % 100000);
  }

  // Print the BST using in-order traversal
  // printInorder(root);

  // Wait for user to press enter
  printf("\nPress enter to continue...");
  getchar();
  getchar(); // To catch the newline character after the number input

  delete root;

  return 0;
}
