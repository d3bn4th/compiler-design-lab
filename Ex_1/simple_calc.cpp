#include <bits/stdc++.h>
using namespace std;

// Balanced Parenthesis check
bool isBalanced(string exp) {
    stack<char> st;
    for (int i = 0; i < exp.size(); i++) {
        if (exp[i] == '(') {
            st.push('(');
        } else if (exp[i] == ')') {
            if (st.empty() || st.top() != '(') {
                return false;
            } else {
                st.pop();
            }
        }
    }
    return st.empty();
}

// To compare precedence of operators
int precedence(char c) {
    if (c == '^') return 3;
    else if (c == '/' || c == '*') return 2;
    else if (c == '+' || c == '-') return 1;
    else return -1;
}

// Postfix conversion function
string toPostfix(string exp) {
    stack<char> st;
    string post;
    for (int i = 0; i < exp.length(); i++) {
        char c = exp[i];
        // Skip spaces
        if (c == ' ') continue;
        // If the scanned character is an operand (handle multi-digit numbers)
        if (isdigit(c)) {
            while (i < exp.length() && isdigit(exp[i])) {
                post += exp[i];
                i++;
            }
            post += ' '; // Add a space to separate numbers
            i--;         // Adjust for the outer loop increment
        }
        // If the scanned character is an '(' push it onto the stack
        else if (c == '(') {
            st.push(c);
        }
        // If the scanned character is an ')', pop and add to postfix until '('
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                post += st.top();
                post += ' '; // Add a space for separation
                st.pop();
            }
            st.pop(); // Pop out '('
        }
        // If an operator is scanned
        else {
            while (!st.empty() && precedence(c) <= precedence(st.top())) {
                post += st.top();
                post += ' '; // Add a space for separation
                st.pop();
            }
            st.push(c);
        }
    }
    // Add all the remaining elements from the stack
    while (!st.empty()) {
        post += st.top();
        post += ' '; // Add a space for separation
        st.pop();
    }
    return post;
}

// Function to evaluate the postfix expression
int evaluate(string s) {
    stack<int> st;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        // Skip spaces
        if (c == ' ') continue;
        // Push multi-digit numbers into the stack
        if (isdigit(c)) {
            int num = 0;
            while (i < s.length() && isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            st.push(num);
            i--; // Adjust for the outer loop increment
        }
        // Operator is scanned
        else {
            int op1 = st.top(); st.pop();
            int op2 = st.top(); st.pop();

            switch (c) {
                case '+': st.push(op2 + op1); break;
                case '-': st.push(op2 - op1); break;
                case '*': st.push(op2 * op1); break;
                case '/': st.push(op2 / op1); break;
                case '^': st.push(pow(op2, op1)); break;
                default: cout << "Error! Invalid operator.\n"; break;
            }
        }
    }
    return st.top();
}

int main() {
    while (true) {
        cout << "Enter the expression > ";
        string exp;
        getline(cin, exp); // Use getline to handle spaces in the input
        if (cin.eof()) {
            cout << " END." << endl;
            break;
        } else {
            // Parenthesis balanced check
            if (!isBalanced(exp)) {
                cout << "Error: Parenthesis not balanced." << endl;
                continue;
            }
            // Postfix conversion
            string post = toPostfix(exp);
            cout << "Postfix Conversion: " << post << endl;

            // Postfix evaluation
            int result = evaluate(post);
            cout << "Result: " << result << endl;
        }
    }

    return 0;
}