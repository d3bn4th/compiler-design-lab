// C++ code to remove left recursion from a given CFG
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void eliminateLeftRecursion(string nt, vector<string> prod){
    vector<string> alpha, beta;
    // alpha : recursive productions
    // beta : non-recursize productions
    for(auto p : prod) {
        if(p[0] == nt[0]){ // if the production starts with nt
            alpha.push_back(p.substr(1)); // rem part after the nt
        }
        else{
            beta.push_back(p); // store prod as is
        }
    }

    // if no recursion found -> print original production
    if(alpha.empty()) { 
        cout << nt  << " -> ";
        for(int i = 0; i < prod.size(); i++) {
            cout << prod[i] << (i < prod.size()-1 ? " | " : "");
        }
        cout << endl;
        return;
    }
    
    // Print new rules
    string ntDash = nt + "'"; // new non terminal : A'
    
    cout << nt << "  -> ";
    for(int i = 0; i < beta.size(); i++) {
        cout << beta[i] << ntDash << (i < beta.size()-1 ? " | " : "");
    } 
    cout << endl;
    
    cout << ntDash << " -> ";
    for(string a : alpha) {
        cout << a << ntDash << " | ";
    }
    cout << "epsilon" << endl;
}

int main() {
    eliminateLeftRecursion("A", {"Aa", "Ab", "b", "c"});
}
