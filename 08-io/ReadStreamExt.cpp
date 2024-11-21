#include <fstream>
#include <iostream>
#include <string>

void read_stream_ext() {
  std::ifstream myfile("example_stream.txt");
  if (myfile.is_open()) {
    std::string line;

    while (!myfile.eof()) {
      getline(myfile, line);
      if (!myfile.eof()) {
        std::cout << line << std::endl;
      }
    }

    myfile.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }
}
