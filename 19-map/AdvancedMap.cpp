#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
  // Create a map from strings to vectors of integers
  std::map<std::string, std::vector<int>> studentGrades;

  // Insert some data into the map
  studentGrades["Alice"] = {85, 92, 78};
  studentGrades["Bob"] = {90, 88, 91};
  studentGrades["Charlie"] = {70, 82, 89};

  // Retrieve and print the data
  for (const auto &student : studentGrades) {
    std::cout << student.first << ": ";
    for (int grade : student.second) {
      std::cout << grade << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}