#include <iostream>
#include <string>
#include <fstream>
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

    cout << "Number of words in the file: " << wordCount << '\n';

    return 0;
}

