#include <iostream>
#include <vector>
#include <string>
using namespace std;

void eliminateLeftRecursion(string nt, vector<string> prod) {
    vector<string> alpha, beta;
    
    // Split into recursive (alpha) and non-recursive (beta) parts
    // "alpha" contains the parts that cause left recursion (they originally started with A)
    // "beta" contains the parts that don't cause left recursion
    for (string p : prod) {
        if (p[0] == nt[0]) // If production starts with non-terminal
            alpha.push_back(p.substr(1)); //Store everything after the first character
        else 
            beta.push_back(p); // Store non-recursive productions as is
    }
    
    // If no recursion found
    if (alpha.empty()) {
        cout << nt << " -> ";
        for (int i = 0; i < prod.size(); i++)
            cout << prod[i] << (i < prod.size()-1 ? " | " : "");
        cout << endl;
        return;
    }
    
    // Print original grammar
    cout << "Original: " << nt << " -> ";
    for (int i = 0; i < prod.size(); i++)
        cout << prod[i] << (i < prod.size()-1 ? " | " : "");
    cout << endl;
    
    // Print new rules
    string ntDash = nt + "'"; // Create new non-terminal A'
    

    cout << nt << " -> ";  // Print A → βA'
    for (int i = 0; i < beta.size(); i++)
        cout << beta[i] << ntDash << (i < beta.size()-1 ? " | " : "");
    cout << endl;
    
    cout << ntDash << " -> ";  // Print A' → αA' | ε
    for (string a : alpha)
        cout << a << ntDash << " | ";
    cout << "ε" << endl;
}

int main() {
    eliminateLeftRecursion("A", {"Aa", "Ab", "b", "c"});
    eliminateLeftRecursion("E", {"E+T","E-T", "T"});
    return 0;
}