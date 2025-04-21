#include <bits/stdc++.h> // Include most standard library headers
using namespace std; // Use names in the standard namespace without qualifying them with std::

// Define a constant d to be used in the hash function
#define d 11

// Function to search for a pattern pat in a text txt using a prime number q
void search(char pat[], char txt[], int q) {
  int M = strlen(pat); // Calculate the length of the pattern
  int N = strlen(txt); // Calculate the length of the text
  int i, j;
  int p = 0; // Initialize the hash value for the pattern
  int t = 0; // Initialize the hash value for the text
  int h = 1; // Initialize a variable h that will be used in the hash function

  // Calculate the hash value h
  for (i = 0; i < M - 1; i++)
    h = (h * d) % q;

  // Calculate the initial hash values for the pattern and the first substring of the text of length M
  for (i = 0; i < M; i++) {
    p = (d * p + pat[i]) % q;
    t = (d * t + txt[i]) % q;
  }

  // Iterate over each substring of the text of length M
  for (i = 0; i <= N - M; i++) {
    // If the hash values of the pattern and the current substring match
    if (p == t) {
      // Check if the actual strings match
      for (j = 0; j < M; j++) {
        if (txt[i + j] != pat[j])
          break;
      }

      // If the actual strings match, print the starting index of the match
      if (j == M)
        cout << "Pattern found at index " << i << endl;
    }

    // If there are still substrings to check
    if (i < N - M) {
      // Update the hash value for the next substring of the text
      t = (d * (t - txt[i] * h) + txt[i + M]) % q;

      // If the hash value is negative, make it positive
      if (t < 0)
        t = (t + q);
    }
  }
}

// Main function
int main() {
  char txt[] = "GEEKS FOR GEEKS"; // Define the text
  char pat[] = "GEEK"; // Define the pattern
  int q = 101; // Define a prime number q
  search(pat, txt, q); // Call the search function with the pattern, text, and q
  return 0; // Return 0 to indicate successful execution
}
