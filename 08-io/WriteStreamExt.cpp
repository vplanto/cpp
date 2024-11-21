// basic file operations
#include <fstream>
#include <iostream>
#include <unistd.h>
using namespace std;

int write_stream_ext() {
  ofstream myfile;
  myfile.open("example_stream.txt");
  for (int i = 0; i < 60; i++) {
    myfile << i << "Writing this to a file\n"; // Action to be performed
  }
  // Intentional segmentation fault to crash the program
  // int *ptr = nullptr;
  // *ptr = 10;
  myfile.flush();
  myfile << "Writing this to a file\n";
  sleep(60); // Pauses the program for ? seconds
  myfile.close();
  return 0;
}
