// obtaining file size
#include <fstream>
#include <iostream>
using namespace std;

int file_size() {
  streampos begin, end;
  ifstream myfile("example_stream.txt", ios::binary);
  begin = myfile.tellg();
  myfile.seekg(0, ios::end);
  end = myfile.tellg();
  myfile.close();
  cout << "size is: " << (end - begin) << " bytes.\n";
  return 0;
}

int main() { return file_size(); };
