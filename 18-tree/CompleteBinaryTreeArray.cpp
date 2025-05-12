#include <iostream> // Include the iostream library
using namespace std; // Use the standard namespace

// Define the maximum number of nodes in the binary tree
#define MAX_NODES 1000

// Define the array to store the nodes of the binary tree
int tree[MAX_NODES];

// Function to insert a node into the binary tree
void insertNode(int data, int index) {
    // If the index is within the range of the array
    if (index < MAX_NODES) {
        tree[index] = data; // Assign the data to the node
    }
}

int main() {
    // Initialize the binary tree to -1
    for (int i = 0; i < MAX_NODES; i++) {
        tree[i] = -1;
    }

    // Insert nodes into the binary tree
    insertNode(1, 0); // Root of the tree
    insertNode(2, 1); // Left child of the root
    insertNode(3, 2); // Right child of the root
    insertNode(4, 3); // Left child of the node with value 2
    insertNode(5, 4); // Right child of the node with value 2

    // The tree will be a complete binary tree

    return 0; // Indicate that the program ran successfully
}
