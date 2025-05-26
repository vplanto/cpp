#include <iostream>
#include <set>

int main() {
    std::set<int> numbers = {4, 2, 5, 1, 3, 2}; // '2' will not be added twice.
    std::cout << "Elements in the set: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Sorting in descending order
    std::set<int, std::greater<int>> descendingSet(numbers.begin(), numbers.end());

    std::cout << "\nElements in descending order: ";
    for (int num : descendingSet) {
        std::cout << num << " ";
    };
    std::cout << std::endl;

    // Check if an element exists
    if (numbers.find(3) != numbers.end()) {
        std::cout << "3 is in the set." << std::endl;
    }

    // Demonstrate removal
    numbers.erase(4);

    std::cout << "After erasing 4: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}