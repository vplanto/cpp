#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string infixToPostfix(const string& infix) {
    string postfix;
    stack<char> opStack;
    
    for (char token : infix) {
        if (isspace(token))
            continue;
        // If token is an operand (here we assume single-digit for simplicity)
        if (isdigit(token)) {
            postfix.push_back(token);
        }
        else if (token == '(') {
            opStack.push(token);
        }
        else if (token == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfix.push_back(opStack.top());
                opStack.pop();
            }
            if (!opStack.empty()) opStack.pop(); // Pop '('
        }
        else { // Operator
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(token)) {
                postfix.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(token);
        }
    }
    
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

