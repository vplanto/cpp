#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

// Функція визначення пріоритету оператора
// Використовується в алгоритмі перетворення інфіксної нотації в постфіксну
int precedence(char op) {
    if (op == '+' || op == '-') return 1;  // Низький пріоритет
    if (op == '*' || op == '/') return 2;  // Високий пріоритет
    return 0;  // Для '(' та інших символів
}

// Алгоритм перетворення інфіксної нотації в постфіксну (зворотна польська нотація)
// Використовує стек для збереження операторів
// Складність: O(n), де n - довжина виразу
string infixToPostfix(const string& infix) {
    string postfix;
    stack<char> opStack;  // Стек для операторів
    
    for (char token : infix) {
        if (isspace(token))
            continue;
        // Якщо токен - операнд (для простоти припускаємо однозначні числа)
        if (isdigit(token)) {
            postfix.push_back(token);  // Додаємо операнд безпосередньо в результат
        }
        else if (token == '(') {
            opStack.push(token);  // '(' завжди додається в стек
        }
        else if (token == ')') {
            // Видаляємо всі оператори до '('
            while (!opStack.empty() && opStack.top() != '(') {
                postfix.push_back(opStack.top());
                opStack.pop();
            }
            if (!opStack.empty()) opStack.pop(); // Видаляємо '('
        }
        else { // Оператор
            // Видаляємо оператори з вищим або рівним пріоритетом
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(token)) {
                postfix.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(token);  // Додаємо поточний оператор в стек
        }
    }
    
    // Видаляємо всі оператори, що залишилися в стеку
    while (!opStack.empty()) {
        postfix.push_back(opStack.top());
        opStack.pop();
    }
    
    return postfix;
}

int main() {
    string expr = "3 + 4 * ( 2 - 1 )";
    string converted = infixToPostfix(expr);
    cout << "Postfix Expression: " << converted << endl;
    return 0;
}

