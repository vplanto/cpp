#include <iostream>

struct tNode {
  int data;
  struct tNode *left;
  struct tNode *right;
};

// Function to create a new node
tNode *newNode(int data) {
  tNode *node = new tNode;
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}

// Function to insert nodes in level order
tNode *insertLevelOrder(int arr[], tNode *root, int i, int n) {
  // Base case for recursion
  if (i < n) {
    tNode *temp = newNode(arr[i]);
    root = temp;

    // insert left child
    root->left = insertLevelOrder(arr, root->left, 2 * i + 1, n);

    // insert right child
    root->right = insertLevelOrder(arr, root->right, 2 * i + 2, n);
  }
  return root;
}

// Function to delete the given tree
void deleteTree(tNode *node) {
  if (node == NULL)
    return;

  /* first delete both subtrees */
  deleteTree(node->left);
  deleteTree(node->right);

  /* then delete the node */
  // std::cout << "Deleting node: " << node->data << std::endl;
  delete node;
}

// Driver program to test above function
int main() {
  int size = 10000000;
  int arr[size]; // Create an array of elements
  for (int i = 0; i < size; i++) {
    arr[i] = i;
  }
  tNode *root = insertLevelOrder(arr, root, 0, size);
  deleteTree(root);
  root = NULL;

  return 0;
}

