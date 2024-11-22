#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int word_counter() {
  ifstream file("example_stream.txt");
  if (!file) {
    cerr << "File could not be opened\n";
    return 1;
  }

  int wordCount = 0;
  string word;

  while (file >> word) {
    ++wordCount;
  }
  file.close();
  cout << "Number of words in the file: " << wordCount << '\n';

  return 0;
}

int main() { return word_counter(); }
