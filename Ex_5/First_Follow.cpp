#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

class FirstAndFollow {
    map<char, vector<string>> rules;    // Stores grammar rules: non-terminal -> list of productions
    map<char, set<char>> first;         // Stores FIRST sets for each symbol
    map<char, set<char>> follow;        // Stores FOLLOW sets for each non-terminal
    char start;                         // Start symbol of grammar
public:
    // Add production rule
    void addRule(char lhs, string rhs) {
        if(rules.empty()) start = lhs;
        rules[lhs].push_back(rhs);
    }

    // Calculate FIRST set
    set<char> getFirst(char symbol) {
        if(first.count(symbol)) return first[symbol];
        
        set<char> result;
        // If terminal, return symbol itself
        if(!isupper(symbol)) {
            result.insert(symbol);
            return result;
        }

        // For each production of this non-terminal
        for(string rhs : rules[symbol]) {
            if(rhs == "e") {  // If epsilon production
                result.insert('e');
            } else {          // Add first char's FIRST set
                set<char> firstSet = getFirst(rhs[0]);
                result.insert(firstSet.begin(), firstSet.end());
            }
        }
        
        first[symbol] = result;
        return result;
    }

    // Calculate FOLLOW set
    void calculateFollow() {
        follow[start].insert('$');  // Add $ to start symbol's FOLLOW

        bool changed;
        do {
            changed = false;
            for(auto& rule : rules) {
                char lhs = rule.first;
                // Process each RHS
                for(string rhs : rule.second) {
                    for(int i = 0; i < rhs.length(); i++) {
                        if(isupper(rhs[i])) {  // If non-terminal
                            int prevSize = follow[rhs[i]].size();
                            
                            // If last symbol, add FOLLOW(LHS)
                            if(i == rhs.length()-1) {
                                follow[rhs[i]].insert(follow[lhs].begin(), follow[lhs].end());
                            }
                            // If not last, add FIRST of next symbol
                            else if(i < rhs.length()-1) {
                                set<char> firstNext = getFirst(rhs[i+1]);
                                follow[rhs[i]].insert(firstNext.begin(), firstNext.end());
                            }

                            if(follow[rhs[i]].size() > prevSize) changed = true;
                        }
                    }
                }
            }
        } while(changed);
    }

    // Print results
    void printSets() {
        // Print FIRST sets
        cout << "\nFIRST Sets:\n";
        for(auto& rule : rules) {
            cout << "FIRST(" << rule.first << ") = { ";
            set<char> f = getFirst(rule.first);
            for(char c : f) cout << c << " ";
            cout << "}\n";
        }

        // Print FOLLOW sets
        cout << "\nFOLLOW Sets:\n";
        for(auto& rule : rules) {
            cout << "FOLLOW(" << rule.first << ") = { ";
            for(char c : follow[rule.first]) cout << c << " ";
            cout << "}\n";
        }
    }
};

int main() {
    FirstAndFollow ff;
    
    cout << "Enter productions (LHS RHS), 'done' to finish\n";
    cout << "Example: E E+T\n";
    cout << "Use 'e' for epsilon\n";

    while(true) {
        string input;
        cout << "> ";
        getline(cin, input);
        if(input == "done") break;
        
        ff.addRule(input[0], input.substr(2));
    }

    ff.calculateFollow();
    ff.printSets();

    return 0;
}