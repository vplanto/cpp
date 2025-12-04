#include <iostream>
using namespace std;

// Наївний алгоритм пошуку підрядка (Naive String Search)
// Складність: O(N * M), де N - довжина тексту, M - довжина патерну
// Принцип: перевіряємо всі можливі позиції в тексті
// Недоліки: повільний, не використовує інформацію про попередні порівняння
void search(string pat, string txt) {
  int M = pat.length();  // Довжина патерну
  int N = txt.length();  // Довжина тексту

  // Перевірка всіх можливих позицій початку патерну в тексті
  for (int i = 0; i <= N - M; i++) {
    int j;
    // Порівняння символів патерну з символами тексту, починаючи з позиції i
    for (j = 0; j < M; j++)
      if (txt[i + j] != pat[j])
        break;  // Неспівпадіння - переходимо до наступної позиції
    if (j == M)  // Всі символи співпали
      cout << "Pattern found at index " << i << endl;
  }
}

int main() {
  string txt = "ABABDABACDABABCABAB";
  string pat = "ABABCABAB";
  search(pat, txt);
  return 0;
}
