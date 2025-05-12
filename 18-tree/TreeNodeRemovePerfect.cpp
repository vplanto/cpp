#include <memory>
#include <vector>
#include <optional>

#include <string>
#include <iostream>

template <typename T>
struct Tree {
    struct Children {
        std::optional<size_t> left = std::nullopt;
        std::optional<size_t> right = std::nullopt;
    };

    std::vector<T> data;
    std::vector<Children> children;

    size_t add(auto&&... args) {
        data.emplace_back(std::forward<decltype(args)>(args)...);
        children.push_back(Children{});
        return data.size()-1;
    }
    size_t add_as_left_child(size_t idx, auto&&... args) {
        size_t cid = add(std::forward<decltype(args)>(args)...);
        children[idx].left = cid;
        return cid;
    }
    size_t add_as_right_child(size_t idx, auto&&... args) {
        size_t cid = add(std::forward<decltype(args)>(args)...);
        children[idx].right = cid;
        return cid;
    }
};


int main() {
    Tree<std::string> tree;
    auto root = tree.add("root node");
    // tree.data[root] == "root node"
    auto left = tree.add_as_left_child(root, "left node");
    // tree.data[left] == "left node", tree.children[root].left == left
    auto right = tree.add_as_right_child(root, "right node");
    // tree.data[right] == "right node", tree.children[root].right == right

    std::cout << tree.data[root] << " - " <<
                tree.data[left] << " - " <<
                tree.data[right] << "\n";
}
