#include <iostream>
#include <map>
#include <string>

int main() {
  // Create a map from strings to integers
  std::map<std::string, int> myMap;

  // Insert some data into the map
  myMap["apple"] = 1;
  myMap["banana"] = 2;
  myMap["cherry"] = 3;

  // Retrieve and print the data
  std::cout << "apple: " << myMap["apple"] << std::endl;
  std::cout << "banana: " << myMap["banana"] << std::endl;
  std::cout << "cherry: " << myMap["cherry"] << std::endl;

  return 0;
}