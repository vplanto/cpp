#include <memory>
#include <string>
#include <iostream>

template <typename T>
struct TreeNode {
    T value = T{};
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;

    TreeNode(const std::string& val, std::unique_ptr<TreeNode> l = nullptr, std::unique_ptr<TreeNode> r = nullptr)
        : value(val), left(std::move(l)), right(std::move(r)) {}
};

int main() {
    auto root = std::make_unique<TreeNode<std::string>>("root node", nullptr, nullptr);
    // root->value == "root node"
    root->left = std::make_unique<TreeNode<std::string>>("left node", nullptr, nullptr);
    // root->left->value == "left node"
    root->right = std::make_unique<TreeNode<std::string>>("right node", nullptr, nullptr);
    // root->right->value == "right node"

    std::cout << root->value << " - " << 
                root->left->value << " - " << 
                root->right->value << "\n";
}
