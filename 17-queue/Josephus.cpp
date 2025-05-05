#include <iostream>
#include <queue>

using namespace std;

int josephus(int n, int k) {
    queue<int> q;
    
    // Initialize the queue with positions 1 through n.
    for (int i = 1; i <= n; i++) {
        q.push(i);
    }
    
    // Elimination process.
    while (q.size() > 1) {
        // Rotate k-1 members by moving them to the back.
        for (int i = 1; i < k; i++) {
            int front = q.front();
            q.pop();
            q.push(front);
        }
        // The kth person is eliminated.
        q.pop();
    }
    
    // The last remaining person is the survivor.
    return q.front();
}

int main() {
    int n, k;
    
    // Input the number of people and the elimination step.
    cout << "Enter the number of people (n): ";
    cin >> n;
    cout << "Enter the elimination step (k): ";
    cin >> k;
    
    int safePosition = josephus(n, k);
    cout << "The safe position is: " << safePosition << endl;
    
    return 0;
}
