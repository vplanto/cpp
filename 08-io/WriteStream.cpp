// basic file operations
#include <fstream>
#include <iostream>
#include <unistd.h>
using namespace std;

int write_stream() {
  ofstream myfile;
  myfile.open("example_stream.txt");
  myfile << "Writing this to a file\n";
  sleep(1); // Pauses the program for ? seconds
  myfile.close();
  return 0;
}
