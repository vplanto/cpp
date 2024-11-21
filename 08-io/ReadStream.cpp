#include <fstream>
#include <iostream>
#include <string>

void read_stream() {
  std::ifstream myfile("example_stream.txt");
  if (myfile.is_open()) {
    std::string line;
    while (getline(myfile, line)) {
      std::cout << line << std::endl;
    }
    myfile.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }
}
