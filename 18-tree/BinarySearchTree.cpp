#include <iostream>
using namespace std;

// Структура вузла бінарного дерева пошуку (BST)
// Властивість BST: для кожного вузла всі елементи лівого піддерева < корінь < всі елементи правого піддерева
struct Node {
    int data;
    Node* left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Вставка елемента в BST
// Складність: O(h), де h - висота дерева (O(log n) у середньому, O(n) у найгіршому)
Node* insert(Node* root, int val) {
    if (!root) return new Node(val);  // Створення нового вузла, якщо дерево порожнє
    
    // Рекурсивна вставка: менші значення - ліворуч, більші - праворуч
    if (val < root->data) root->left = insert(root->left, val);  // Вставка ліворуч
    else root->right = insert(root->right, val);  // Вставка праворуч

    return root;
}

// Обхід дерева в порядку "внутрішній" (Inorder)
// Для BST дає відсортовану послідовність елементів
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
    inorderTraversal(root);  // Виведе: 20 30 40 50 70 (відсортовано)

    return 0;
}