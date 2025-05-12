#include <memory>
#include <vector>
#include <functional>
#include <iostream>
#include <queue>

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

void rank_order(Node* root, const std::function<void(Node*)>& visitor) {
    std::queue<Node*> q;
    if (root != nullptr)
        q.push(root);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        if (current == nullptr) continue;
        visitor(current);
        q.push(current->left);
        q.push(current->right);
    }
}

std::vector<int> max_at_level(Node* root) {
    std::vector<int> result;
    std::queue<std::pair<Node*,size_t>> q;
    if (root != nullptr)
        q.push({root,0});
    while (!q.empty()) {
        auto [node,rank] = q.front();
        q.pop();
        if (result.size() <= rank)
            result.push_back(node->value);
        else
            result[rank] = std::max(result[rank], node->value);
        if (node->left != nullptr)
            q.push({node->left,rank+1});
        if (node->right != nullptr)
            q.push({node->right, rank+1});
    }
    return result;
}

int main() {
    Tree<int> tree;
    auto root = tree.root = tree.add(1);
    auto left = root->left = tree.add(2);
    auto right = root->right = tree.add(3);
    left->left = tree.add(4);
    left->right = tree.add(5);
    right->left = tree.add(6);
    right->right = tree.add(7);

    rank_order(root, [](Node* node){
        std::cout << node->value << " ";
    });
    std::cout << "\n";
    // prints: 1 2 3 4 5 6 7

    for (auto v : max_at_level(tree.root)) {
        std::cout << v << " ";
    }
    std::cout << "\n";
    // prints: 1 3 7
}