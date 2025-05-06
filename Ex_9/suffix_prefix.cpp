#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

// Function to check if character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to get precedence of operator
int getPrecedence(char c) {
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
}

// Function to convert infix to prefix
string infixToPrefix(string infix) {
    // Reverse the infix expression
    reverse(infix.begin(), infix.end());
    
    stack<char> operators;
    string prefix = "";
    
    for (char c : infix) {
        if (isalnum(c)) {
            prefix += c;
        }
        else if (c == ')') {
            operators.push(c);
        }
        else if (c == '(') {
            while (!operators.empty() && operators.top() != ')') {
                prefix += operators.top();
                operators.pop();
            }
            if (!operators.empty())
                operators.pop();
        }
        else if (isOperator(c)) {
            while (!operators.empty() && operators.top() != ')' && 
                   getPrecedence(operators.top()) > getPrecedence(c)) {
                prefix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }
    
    while (!operators.empty()) {
        prefix += operators.top();
        operators.pop();
    }
    
    // Reverse the final result
    reverse(prefix.begin(), prefix.end());
    return prefix;
}

// Function to convert infix to postfix (suffix)
string infixToPostfix(string infix) {
    stack<char> operators;
    string postfix = "";
    
    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        }
        else if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            if (!operators.empty())
                operators.pop();
        }
        else if (isOperator(c)) {
            while (!operators.empty() && operators.top() != '(' && 
                   getPrecedence(operators.top()) >= getPrecedence(c)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }
    
    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }
    
    return postfix;
}

int main() {
    string infix;
    cout << "Enter an infix expression (e.g., a+b*c): ";
    cin >> infix;
    
    string prefix = infixToPrefix(infix);
    string postfix = infixToPostfix(infix);
    
    cout << "Infix Expression: " << infix << endl;
    cout << "Prefix Expression: " << prefix << endl;
    cout << "Postfix Expression: " << postfix << endl;
    
    return 0;
}
