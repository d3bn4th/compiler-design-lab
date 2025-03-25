#include <iostream>
#include <vector>
#include <string>
using namespace std;

string getCommonPrefix(vector<string> prod){
    string prefix = "";
    string first = prod[0]; // pick the first stirng
    for(int i = 0; i < first.size(); i++) {
        char current = first[i];
        for(string p : prod) {
            if(i >= p.length() || p[i] != current) {
                return prefix;
            }
        }
        prefix += current;
    }
    return prefix;
}

void leftFactoring(string nt, vector<string> prod) {
    string prefix = getCommonPrefix(prod);

    // Print the original grammar
    cout << "Original Grammar : " << endl;
    cout << nt << " -> ";
    for(int i = 0; i < prod.size(); i++) {
        cout << prod[i] << (i < prod.size()-1? " | ": "");
    }
    cout << endl;

    // Declare a new non terminal
    string ntDash = nt + "'";
    // Print the factored grammar
    cout << "Factored Grammar : " << endl;
    cout << nt << " -> " << prefix << ntDash  << endl;
    cout << ntDash << " -> ";
    for(int i = 0; i < prod.size(); i++) {
        string suffix = prod[i].substr(prefix.length());
        cout << (suffix.empty() ? "ε" : suffix);
        cout << (i < prod.size()-1 ? " | " : "");
    }
    cout << endl;
}

int main() {
    leftFactoring("S", {"bcr", "bcs", "bct"});
    return 0;
}