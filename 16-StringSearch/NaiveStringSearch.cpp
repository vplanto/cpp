#include <iostream>
using namespace std;

void search(string pat, string txt) {
  int M = pat.length();
  int N = txt.length();

  for (int i = 0; i <= N - M; i++) {
    int j;
    for (j = 0; j < M; j++)
      if (txt[i + j] != pat[j])
        break;
    if (j == M)
      cout << "Pattern found at index " << i << endl;
  }
}

int main() {
  string txt = "ABABDABACDABABCABAB";
  string pat = "ABABCABAB";
  search(pat, txt);
  return 0;
}
