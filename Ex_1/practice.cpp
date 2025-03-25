#include<bits/stdc++.h>
using namespace std;

int precedence(char c){
    if(c == '^') return 3;
    if(c == '/' || c == '*') return 2;
    if(c == '+' || c == '-') return 1;
    else return -1;
}

string toPostfix(string exp) {
    stack<char> st;
    string post;
    for(int i = 0; i < exp.length(); i++) {
        char c = exp[i];
        if(c == ' ') continue;
        // is c is an operand(multi-digit)
        else if(isdigit(c)){
            while(i < exp.length() && isdigit(exp[i])){
                post += exp[i];
                i++;
            }
            post += ' '; // Add a space to seperate numbers
            i--; // Adjust for the outer loop increment
        }
        // if c is an '('
        else if(c == '(') {
            st.push(c);
        } 
        // if c is a ')'
        else if(c == ')') {
            while(!st.empty() && st.top() != '(') {
                post += st.top();
                post += ' '; // for seperation
                st.pop();
            }
            st.pop(); // Pop out the '('
        }
        // if c is an operand
        else {
            while(!st.empty() && precedence(c) <= precedence(st.top())) {
                post += st.top();
                post += ' '; // for seperation 
                st.pop();
            }
            st.push(c);
        }
    }
    // add the remaining elements to the post exp 
    while(!st.empty()){
        post += st.top();
        post += ' '; // for seperation 
        st.pop(); 
    }
    return post;
}

// Function to evaluate the postfix expression
int evaluate(string post) {
    stack<int> st;
    for(int i = 0; i < post.length(); i++) {
        
    }
}


int main(){
    cout << "Enter the expression: "; 
    string exp;
    getline(cin,exp);
    cout << toPostfix(exp) << endl;
    return 0;
}