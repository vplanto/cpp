#include <memory>
#include <vector>
#include <functional>
#include <iostream>
#include <stack>

template <typename T>
struct Tree {
    struct Node {
        T value = T{};
        Node* left = nullptr;
        Node* right = nullptr;
    };
    Node* add(auto&& ... args) {
        storage_.push_back(std::make_unique<Node>(std::forward<decltype(args)>(args)...));
        return storage_.back().get();
    }
    Node* root;
private:
    std::vector<std::unique_ptr<Node>> storage_;
};

using Node = Tree<int>::Node;

// pre-order traversal
void pre_order(Node *node, const std::function<void(Node*)>& visitor) {
    if (node == nullptr) return;
    visitor(node);
    pre_order(node->left, visitor);
    pre_order(node->right, visitor);
}

// serialization using pre-order traversal
void serialize(Node *node, std::ostream& s) {
    if (node == nullptr) {
        s << 0 << " ";
        return;
    }
    s << node->value << " ";
    serialize(node->left, s);
    serialize(node->right, s);
}

// deserialization using pre-order traversal
Tree<int>::Node *deserialize_single(Tree<int>& tree, std::istream& s) {
    int value = 0;
    if (!(s >> value) || value <= 0) return nullptr;
    return tree.add(value);
}

Tree<int>::Node *deserialize(Tree<int>& tree, std::istream& s) {
    auto node = deserialize_single(tree, s);
    if (node == nullptr) return node;
    node->left = deserialize(tree, s);
    node->right = deserialize(tree, s);
    return node;
}

void pre_order_stack(Node* root, const std::function<void(Node*)>& visitor) {
    std::stack<Node*> stack;
    stack.push(root);
    while (!stack.empty()) {
        Node *curr = stack.top();
        stack.pop();
        visitor(curr);
        // With this approach we visit "null" nodes, which can be useful.
        // Alternatively we could move the condition to the push:
        // if (curr->right != nullptr) stack.push(curr->right);
        if (curr == nullptr) continue;

        // If we want to maintain the same ordering as recursive pre-order, 
        // we need to insert in reverse.
        stack.push(curr->right);
        stack.push(curr->left);
    }
}

int main() {
    Tree<int> tree;
    // deserialize
    tree.root = deserialize(tree, std::cin);
    // serialize
    serialize(tree.root, std::cout);
    std::cout << "\n";

    // Demonstrating the non-recursive pre-order
    // same serialization output as serialize()
    pre_order_stack(tree.root, [](Node* node) {
        if (node == nullptr)
            std::cout << 0 << " ";
        else
            std::cout << node->value << " ";
    });
    std::cout << "\n";
}