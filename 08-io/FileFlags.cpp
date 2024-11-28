#include <fstream>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

int main() {
  // Open the file for reading
  ifstream file("example_stream.txt");

  if (!file) {
    cerr << "Error opening file for reading." << endl;
    return 1;
  }

  // Variables to hold file data
  string line;

  // Read and process data
  while (getline(file, line)) {
    if (file.bad()) {
      cerr << "Bad file operation." << endl;
      break;
    } else if (file.fail()) {
      cerr << "Fail bit set - possible format error or read error." << endl;
      file.clear();  // Reset fail state
      file.ignore(numeric_limits<streamsize>::max(),
                  '\n');  // Skip the problematic line
    } else if (file.eof()) {
      cout << "Reached end of file." << endl;
      break;
    } else if (file.good()) {
      cout << "Read line: " << line << endl;
    }
  }

  // Clear flags and close the file
  file.clear();
  file.close();

  // Attempt to open the file for writing to demonstrate error handling
  ofstream outfile("example_stream.txt", ios::app);
  if (!outfile) {
    cerr << "Error opening file for writing." << endl;
    return 1;
  }

  // Simulate write operation and check state
  outfile << "Adding new line to file." << endl;
  if (outfile.bad()) {
    cerr << "Bad write operation." << endl;
  } else if (outfile.fail()) {
    cerr << "Fail bit set during write operation." << endl;
  } else if (outfile.good()) {
    cout << "Write operation successful." << endl;
  }

  // Clear flags and close the file
  outfile.clear();
  outfile.close();

  return 0;
}
