#include <memory>
#include <vector>
#include <functional>
#include <iostream>
#include <optional>
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

struct Eventual {
    std::optional<int> result;
    std::function<int(const Eventual& l, const Eventual& r)> op;
};

using Node = Tree<Eventual>::Node;

// post-order traversal
void post_order(Node *node, const std::function<void(Node*)>& visitor) {
    if (node == nullptr) return;
    post_order(node->left, visitor);
    post_order(node->right, visitor);
    visitor(node);
}

void post_order_nonrecursive(Node *root, const std::function<void(Node*)>& visitor) {
    std::stack<Node*> s;
    Node *current = root;
    while (true) {
        // Explore left, but remember node & right child
        if (current != nullptr) {
            if (current->right != nullptr)
                s.push(current->right);
            s.push(current);
            current = current->left;
            continue;
        }
        // current == nullptr
        if (s.empty()) return;
        current = s.top();
        s.pop();
        // If we have the right child remembered, 
        // it would be on the top of the stack.
        if (current->right && !s.empty() && current->right == s.top()) {
            // if it is, we must visit it (and it's children) first
            s.pop();
            s.push(current);
            current = current->right;
        } else {
            visitor(current);
            current = nullptr;
        }
    }
}

int main() {
    Tree<Eventual> tree;
    auto plus = [](const Eventual& l, const Eventual& r) {
        return *l.result + *r.result;
    };
    auto minus = [](const Eventual& l, const Eventual& r) {
        return *l.result - *r.result;
    };
    auto times = [](const Eventual& l, const Eventual& r) {
        return *l.result * *r.result;
    };
    // encode (4-2)*(2+1)
    auto root = tree.root = tree.add(Eventual{std::nullopt, times});
    auto left = root->left = tree.add(Eventual{std::nullopt, minus});
    auto right = root->right = tree.add(Eventual{std::nullopt, plus});
    left->left = tree.add(Eventual{4, {}});
    left->right = tree.add(Eventual{2, {}});
    right->left = tree.add(Eventual{2, {}});
    right->right = tree.add(Eventual{1, {}});

    post_order(tree.root, [](Node* node) {
        // if this node already has a result value, we don't have to do anything
        if (node->value.result) return;
        // if it is an operation, evaluate post-order guarantees 
        // that node->left->value and node->right->value both have result values
        node->value.result = node->value.op(node->left->value, node->right->value);
    });
    std::cout << *tree.root->value.result << "\n";

    post_order_nonrecursive(tree.root, [](Node* node) {
        std::cout << *node->value.result << " ";
    });
    std::cout << "\n";
}
