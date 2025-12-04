#include <iostream>
#include <queue>

using namespace std;

// Задача Йосипа (Josephus Problem)
// Знаходження останньої людини, що залишиться, коли кожна k-та людина видаляється
// Складність: O(n * k), де n - кількість людей, k - крок видалення
int josephus(int n, int k) {
    queue<int> q;
    
    // Ініціалізація черги позиціями від 1 до n
    for (int i = 1; i <= n; i++) {
        q.push(i);
    }
    
    // Процес видалення
    while (q.size() > 1) {
        // Обертання k-1 членів, переміщуючи їх в кінець
        // Це "рахуємо" до k-ї людини
        for (int i = 1; i < k; i++) {
            int front = q.front();
            q.pop();
            q.push(front);  // Переміщення в кінець (обертання)
        }
        // k-та людина видаляється
        q.pop();
    }
    
    // Остання людина, що залишилася - виживша
    return q.front();
}

int main() {
    int n, k;
    
    cout << "Enter the number of people (n): ";
    cin >> n;
    cout << "Enter the elimination step (k): ";
    cin >> k;
    
    int safePosition = josephus(n, k);
    cout << "The safe position is: " << safePosition << endl;
    
    return 0;
}
