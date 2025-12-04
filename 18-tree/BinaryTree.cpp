#include <bits/stdc++.h>
using namespace std;

// Клас вузла для визначення структури вузла бінарного дерева
class Node {
public:
  int data;        // Дані вузла
  Node *left, *right;  // Вказівники на ліве та праве піддерева
  // Параметризований конструктор
  Node(int val) {
    data = val;
    left = right = NULL;
  }
};

// Функція вставки вузлів у бінарне дерево
// Вставка відбувається на рівні порядку (level order) - заповнює дерево зліва направо
// Складність: O(n) - прохід по дереву
Node *insert(Node *root, int data) {
  // Якщо дерево порожнє, новий вузол стає коренем
  if (root == NULL) {
    root = new Node(data);
    return root;
  }
  // Черга для обходу дерева та знаходження позиції для вставки вузла
  queue<Node *> q;
  q.push(root);
  while (!q.empty()) {
    Node *temp = q.front();
    q.pop();
    // Вставка вузла як лівого дочірнього вузла батьківського вузла
    if (temp->left == NULL) {
      temp->left = new Node(data);
      break;
    }
    // Якщо лівий дочірній вузол не NULL, додаємо його в чергу
    else
      q.push(temp->left);
    // Вставка вузла як правого дочірнього вузла батьківського вузла
    if (temp->right == NULL) {
      temp->right = new Node(data);
      break;
    }
    // Якщо правий дочірній вузол не NULL, додаємо його в чергу
    else
      q.push(temp->right);
  }
  return root;
}

/* Функція видалення найглибшого вузла (d_node) у бінарному дереві */
// Використовується для видалення вузла з дерева
void deletDeepest(Node *root, Node *d_node) {
  queue<Node *> q;
  q.push(root);
  // Обхід дерева в порядку рівнів до останнього вузла
  Node *temp;
  while (!q.empty()) {
    temp = q.front();
    q.pop();
    if (temp == d_node) {
      temp = NULL;
      delete (d_node);
      return;
    }
    if (temp->right) {
      if (temp->right == d_node) {
        temp->right = NULL;
        delete (d_node);
        return;
      } else
        q.push(temp->right);
    }
    if (temp->left) {
      if (temp->left == d_node) {
        temp->left = NULL;
        delete (d_node);
        return;
      } else
        q.push(temp->left);
    }
  }
}

/* Функція видалення елемента з бінарного дерева */
// Алгоритм: знаходимо вузол для видалення, замінюємо його найглибшим вузлом
// Складність: O(n) - обхід дерева
Node *deletion(Node *root, int key) {
  if (!root)
    return NULL;
  if (root->left == NULL && root->right == NULL) {
    if (root->data == key)
      return NULL;
    else
      return root;
  }
  queue<Node *> q;
  q.push(root);
  Node *temp;
  Node *key_node = NULL;
  // Обхід дерева в порядку рівнів для знаходження найглибшого вузла (temp)
  // та вузла для видалення (key_node)
  while (!q.empty()) {
    temp = q.front();
    q.pop();
    if (temp->data == key)
      key_node = temp;
    if (temp->left)
      q.push(temp->left);
    if (temp->right)
      q.push(temp->right);
  }
  if (key_node != NULL) {
    int x = temp->data;  // Дані найглибшого вузла
    key_node->data = x;   // Заміна даних вузла для видалення
    deletDeepest(root, temp);  // Видалення найглибшого вузла
  }
  return root;
}

// Обхід дерева в порядку "внутрішній" (Inorder: Left - Root - Right)
// Для бінарного дерева пошуку дає відсортовану послідовність
// Складність: O(n)
void inorderTraversal(Node *root) {
  if (!root)
    return;
  inorderTraversal(root->left);
  cout << root->data << " ";
  inorderTraversal(root->right);
}

// Обхід дерева в порядку "перед" (Preorder: Root - Left - Right)
// Використовується для копіювання дерева, серіалізації
// Складність: O(n)
void preorderTraversal(Node *root) {
  if (!root)
    return;
  cout << root->data << " ";
  preorderTraversal(root->left);
  preorderTraversal(root->right);
}

// Обхід дерева в порядку "після" (Postorder: Left - Right - Root)
// Використовується для видалення дерева, обчислення виразів
// Складність: O(n)
void postorderTraversal(Node *root) {
  if (root == NULL)
    return;
  postorderTraversal(root->left);
  postorderTraversal(root->right);
  cout << root->data << " ";
}

// Функція обходу дерева в порядку рівнів (Level order / Breadth-First)
// Використовує чергу для обходу рівень за рівнем
// Складність: O(n)
void levelorderTraversal(Node *root) {
  if (root == NULL)
    return;

  // Черга для обходу в порядку рівнів
  queue<Node *> q;
  q.push(root);
  while (!q.empty()) {
    Node *temp = q.front();
    q.pop();
    cout << temp->data << " ";
    // Додавання лівого дочірнього вузла в чергу
    if (temp->left)
      q.push(temp->left);
    // Додавання правого дочірнього вузла в чергу
    if (temp->right)
      q.push(temp->right);
  }
}

/* Driver function to check the above algorithm. */
int main() {
  Node *root = NULL;
  // Insertion of nodes
  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 30);
  root = insert(root, 40);

  cout << "Preorder traversal: ";
  preorderTraversal(root);

  cout << "\nInorder traversal: ";
  inorderTraversal(root);

  cout << "\nPostorder traversal: ";
  postorderTraversal(root);

  cout << "\nLevel order traversal: ";
  levelorderTraversal(root);

  // Delete the node with data = 20
  root = deletion(root, 20);

  cout << "\nInorder traversal after deletion: ";
  inorderTraversal(root);
}
