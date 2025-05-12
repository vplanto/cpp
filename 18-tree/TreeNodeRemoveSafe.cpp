#include <memory>
#include <vector>
#include <string>
#include <iostream>

template <typename T>
struct Tree {
    struct Node {
        T value = T{};
        Node* left = nullptr;
        Node* right = nullptr;
    };
    //Use g++ -std=c++20 for compile
    Node* add(auto&& ... args) {
        storage_.push_back(std::make_unique<Node>(std::forward<decltype(args)>(args)...));
        return storage_.back().get();
    }
    Node* root;
private:
    std::vector<std::unique_ptr<Node>> storage_;
};

int main() {
    Tree<std::string> tree;
    tree.root = tree.add("root node");
    // tree.root->value == "root node"
    tree.root->left = tree.add("left node");
    // tree.root->left->value == "left node"
    tree.root->right = tree.add("right node");
    // tree.root->right->value == "right node"

    std::cout << tree.root->value << " - " << 
                tree.root->left->value << " - " << 
                tree.root->right->value << "\n";
}
