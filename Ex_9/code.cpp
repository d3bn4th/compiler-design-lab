#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
 
using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int getPrecedence(char c) {
    if(c == '*' || c == '/') return 2;
    if(c == '+' || c == '-') return 1;
    return 0;
}

// Postfix(Suffix Notation)
string toPostfix(string input) {
    stack<char> st;
    string postfix = "";

    for(char c : input) {
        if(isalnum(c)) {
            postfix += c;
        }
        else if(c == '(') {
            st.push(c);
        }
        else if(c == ')') {
            while(!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            if(!st.empty()){
                st.pop(); // pop (
            }
        }
        else if(isOperator(c)) {
            while(!st.empty() && st.top() != '(' && getPrecedence(c) <= getPrecedence(st.top())) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    // add the remainning to postfix
    while(!st.empty()) {
        postfix += st.top();
        st.pop();
    }
    
    return postfix;
}

// Prefix Notation
string toPrefix(string input) {
    reverse(input.begin(), input.end());
    for(char &c : input) {
        if(c == '(') c = ')';
        else if(c == ')') c = '(';
    }
    string postfix = toPostfix(input);
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

int main() {
    string input;
    cout << "Enter an infix expression(e.g a+b*c): ";
    cin >> input;
    string prefix = toPrefix(input);
    string postfix = toPostfix(input);

    cout << "Infix Expression: " << input << endl;
    cout << "Prefix Expression: " << prefix << endl;
    cout << "Postfix Expression: " << postfix << endl;
    
    return 0;
}