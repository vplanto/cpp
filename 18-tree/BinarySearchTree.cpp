#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int val) {
    if (!root) return new Node(val);  // Create a new node
    
    if (val < root->data) root->left = insert(root->left, val);  // Insert left
    else root->right = insert(root->right, val);  // Insert right

    return root;
}

void inorderTraversal(Node* root) {
    if (!root) return;
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

int main() {
    Node* root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    
    cout << "Inorder Traversal: ";
    inorderTraversal(root);

    return 0;
}