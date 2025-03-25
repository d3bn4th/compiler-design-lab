#include <iostream>
#include <vector>
#include <string>
using namespace std;

string getCommonPrefix(vector<string> prod) {
    if (prod.empty()) return "";
    string prefix = "";
    string first = prod[0];
    
    for (int i = 0; i < first.length(); i++) {
        char current = first[i];
        for (string p : prod) {
            if (i >= p.length() || p[i] != current) 
                return prefix;
        }
        prefix += current;
    }
    return prefix;
}

void leftFactoring(string nt, vector<string> prod) {
    string prefix = getCommonPrefix(prod);
    
    if (prefix.empty()) {
        cout << "No left factoring needed" << endl;
        return;
    }
    
    string ntDash = nt + "'";
    
    // Print original grammar
    cout << "Original: " << nt << " -> ";
    for (int i = 0; i < prod.size(); i++)
        cout << prod[i] << (i < prod.size()-1 ? " | " : "");
    cout << endl;
    
    // Print factored grammar
    cout << "Factored: " << endl;
    cout << nt << " -> " << prefix << ntDash << endl;
    
    cout << ntDash << " -> ";
    for (int i = 0; i < prod.size(); i++) {
        string suffix = prod[i].substr(prefix.length());
        cout << (suffix.empty() ? "ε" : suffix) << (i < prod.size()-1 ? " | " : "");
    }
    cout << endl;
}

int main() {
    leftFactoring("A", {"abc", "abd", "abe", "xy"});
    leftFactoring("S", {"bcr", "bcs", "bct"});
    return 0;
}