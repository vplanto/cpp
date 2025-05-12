#include <iostream>  // Include the iostream library
using namespace std; // Use the standard namespace

// Define the structure for the nodes of the binary tree
struct Node {
  int data;    // The data in the node
  Node *left;  // Pointer to the left child node
  Node *right; // Pointer to the right child node
};

// Function to create a new node with the given data
Node *createNode(int data) {
  Node *newNode = new Node(); // Create a new node
  if (!newNode) {
    cout << "Memory error\n";
    return NULL;
  }
  newNode->data = data;                  // Assign the data
  newNode->left = newNode->right = NULL; // Initialize the child nodes to NULL
  return newNode;                        // Return the new node
}

// Function to insert a node into the binary tree
Node *insertNode(Node *root, int data) {
  // If the tree is empty, assign a new node address to the root
  if (root == NULL) {
    root = createNode(data);
    return root;
  }

  // Else, do level order traversal until we find an empty
  // place, i.e. either left child or right child of some
  // node is pointing to NULL.
  queue<Node *> q;
  q.push(root);

  while (!q.empty()) {
    Node *temp = q.front();
    q.pop();

    if (temp->left != NULL)
      q.push(temp->left);
    else {
      temp->left = createNode(data);
      return root;
    }

    if (temp->right != NULL)
      q.push(temp->right);
    else {
      temp->right = createNode(data);
      return root;
    }
  }
  return root;
}

int main() {
  Node *root = NULL; // Start with an empty tree

  // Insert nodes into the binary tree
  root = insertNode(root, 1);
  root = insertNode(root, 2);
  root = insertNode(root, 3);
  root = insertNode(root, 4);
  root = insertNode(root, 5);

  // The tree will be a complete binary tree

  return 0; // Indicate that the program ran successfully
}
