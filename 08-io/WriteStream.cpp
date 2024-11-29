// basic file operations
#include <unistd.h>

#include <fstream>
using namespace std;

int write_stream() {
  ofstream myfile;
  myfile.open("example_stream.txt", ios::app);
  myfile << "Writing this to a file\n";
  sleep(1);  // Pauses the program for ? seconds
  myfile.close();
  return 0;
}

int main() { return write_stream(); };
