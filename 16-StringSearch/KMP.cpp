#include <bits/stdc++.h> // Include most standard library headers
using namespace std; // Use names in the standard namespace without qualifying
                     // them with std::

// Forward declaration of function to compute the longest proper prefix which is
// also proper suffix array
void computeLPSArray(char *pat, int M, int *lps);

// Function to search for a pattern pat in a text txt using the KMP algorithm
void KMPSearch(char *pat, char *txt) {
  int M = strlen(pat); // Calculate the length of the pattern
  int N = strlen(txt); // Calculate the length of the text

  int lps[M]; // Array to hold longest prefix suffix values for pattern

  computeLPSArray(pat, M, lps); // Fill lps[] for given pattern string

  int i = 0;      // Index for txt[]
  int j = 0;      // Index for pat[]
  while (i < N) { // Iterate over the text
    if (pat[j] ==
        txt[i]) { // If current characters match, increment both i and j
      j++;
      i++;
    }

    if (j == M) { // If we found a match
      printf("Found pattern at index %d \n", i - j);
      j = lps[j - 1]; // Get the next state of pattern from lps[] array
    }

    else if (i < N && pat[j] != txt[i]) { // Mismatch after j matches
      if (j != 0) // If j is not 0, start matching with the next character in
                  // the pattern
        j = lps[j - 1];
      else // If j is 0, start matching with the next character in the text
        i = i + 1;
    }
  }
}

// Function to compute the longest proper prefix which is also proper suffix
// array
void computeLPSArray(char *pat, int M, int *lps) {
  int len = 0; // Length of the previous longest prefix suffix

  lps[0] = 0; // lps[0] is always 0

  int i = 1; // Loop variable
  // The loop calculates lps[i] for i = 1 to M-1
  while (i < M) {
    if (pat[i] == pat[len]) { // If pat[i] == pat[len], increment len and assign
                              // it to lps[i]
      len++;
      lps[i] = len;
      i++;
    } else {          // If pat[i] != pat[len]
      if (len != 0) { // If len is not 0, then go back to the previous character
        len = lps[len - 1];
      } else { // If len is 0, then assign lps[i] = 0 and move to the next
               // character
        lps[i] = 0;
        i++;
      }
    }
  }
}

// Main function
int main() {
  char txt[] = "ABABDABACDABABCABAB"; // Define the text
  char pat[] = "ABABCABAB";           // Define the pattern
  KMPSearch(pat, txt); // Call the KMPSearch function with the pattern and text
  return 0;            // Return 0 to indicate successful execution
}
